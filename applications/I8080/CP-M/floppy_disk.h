#pragma once

#include <cstdio>
#include <fstream>
#include <filesystem>
#include <cstring>
#include <algorithm>
#include <mutex>
#include "core/compilers_macro.h"
#include "core/types.h"
#include "io_device.h"
#include "memory.h"
#include "logger.h"
#include <sstream>
#include <iomanip>

class FloppyDisk : public IO_Device<WORD> {
public:
    static constexpr WORD CMD_PORT = 0x10;
    static constexpr WORD TRACK_PORT = 0x11;
    static constexpr WORD SECTOR_PORT = 0x12;
    static constexpr WORD DMA_LOW_PORT = 0x13;
    static constexpr WORD DMA_HIGH_PORT = 0x14;
    static constexpr WORD DRIVE_SELECT_PORT = 0x15;

    static constexpr BYTE CMD_READ = 1;
    static constexpr BYTE CMD_WRITE = 2;

    static constexpr int TRACKS = 77;
    static constexpr int SECTORS_PER_TRACK = 26;
    static constexpr int SECTOR_SIZE = 128;

    static constexpr int BLOCK_SIZE = 1024;
    static constexpr int SYSTEM_TRACKS = 2;
    static constexpr int MAX_BLOCKS = 242;
    static constexpr int DIR_ENTRIES = 64;
    static constexpr int MAX_DRIVES = 4;
    static constexpr size_t DIR_OFFSET = SYSTEM_TRACKS * SECTORS_PER_TRACK * SECTOR_SIZE;

    struct Drive {
        std::fstream image;
        size_t nextFreeBlock = 2;
    };

    FloppyDisk() = default;

    void setMemory(Memory<WORD> &mem) {
        memory = &mem;
        memSize = mem.Size();
    }

    ~FloppyDisk() {
        std::lock_guard lock(disk_mtx);
        for (auto &d: drives) {
            if (d.image.is_open())
                d.image.close();
        }
    }

    bool openDisk(const std::filesystem::path &path, int drive = 0) {
        std::lock_guard lock(disk_mtx);
        if (drive < 0 || drive >= MAX_DRIVES)
            return false;
        drives[drive].image.open(path, std::ios::in | std::ios::out | std::ios::binary);
        return drives[drive].image.is_open();
    }

    static bool createEmptyDisk(const std::filesystem::path &path) {
        std::ofstream out(path, std::ios::binary | std::ios::trunc);
        if (!out.is_open())
            return false;
        std::vector<BYTE> empty(SECTOR_SIZE, 0xE5);
        for (int i = 0; i < TRACKS * SECTORS_PER_TRACK; i++) {
            out.write(reinterpret_cast<const char *>(empty.data()), SECTOR_SIZE);
        }
        return out.good();
    }

    bool injectFile(const std::filesystem::path &hostPath, const std::string &cpmName, int drive = 0) {
        std::lock_guard lock(disk_mtx);
        if (drive < 0 || drive >= MAX_DRIVES)
            return false;
        if (!drives[drive].image.is_open())
            return false;

        auto &diskImage = drives[drive].image;
        auto &nextFreeBlock = drives[drive].nextFreeBlock;

        std::ifstream hostFile(hostPath, std::ios::binary | std::ios::ate);
        if (!hostFile.is_open())
            return false;

        size_t fileSize = hostFile.tellg();
        hostFile.seekg(0);

        if (fileSize == 0)
            return false;

        std::vector<BYTE> fileData(fileSize);
        hostFile.read(reinterpret_cast<char *>(fileData.data()), fileSize);

        auto [name8, ext3] = parseCpmName(cpmName);

        static constexpr int BLOCKS_PER_EXTENT = 16;
        static constexpr int RECORDS_PER_EXTENT = 128;
        int numBlocks = (static_cast<int>(fileSize) + (BLOCK_SIZE - 1)) / BLOCK_SIZE;
        int numRecords = (static_cast<int>(fileSize) + 127) / 128;
        int numExtents = (numBlocks + BLOCKS_PER_EXTENT - 1) / BLOCKS_PER_EXTENT;

        if (numExtents > 32) {
            fprintf(stderr, "INJECT ERR: %s too large (needs %d extents, >512KB)\n",
                    cpmName.c_str(), numExtents);
            return false;
        }

        nextFreeBlock = std::max<size_t>(findMaxBlock(diskImage) + 1, 2);

        if (numBlocks < 1 ||
            nextFreeBlock + static_cast<size_t>(numBlocks) - 1 > MAX_BLOCKS) {
            fprintf(stderr, "INJECT ERR: %s does not fit (need %d blocks, block %zu..%zu)\n",
                    cpmName.c_str(), numBlocks, nextFreeBlock,
                    nextFreeBlock + static_cast<size_t>(numBlocks) - 1);
            return false;
        }

        if (countFreeDirEntries(diskImage) < numExtents) {
            fprintf(stderr, "INJECT ERR: %s needs %d dir entries, not enough free\n",
                    cpmName.c_str(), numExtents);
            return false;
        }

        std::vector<BYTE> blockAlloc(numBlocks);
        for (int i = 0; i < numBlocks; i++) {
            blockAlloc[i] = nextFreeBlock++;
        }

        for (int i = 0; i < numBlocks; i++) {
            size_t blockOffset = DIR_OFFSET +
                                 static_cast<size_t>(blockAlloc[i]) * BLOCK_SIZE;
            size_t srcOff = static_cast<size_t>(i) * BLOCK_SIZE;
            size_t chunkSize = std::min(static_cast<size_t>(BLOCK_SIZE), fileSize - srcOff);
            diskImage.seekp(blockOffset);
            diskImage.write(reinterpret_cast<const char *>(fileData.data() + srcOff), chunkSize);
            if (chunkSize < BLOCK_SIZE) {
                std::vector<BYTE> pad(BLOCK_SIZE - chunkSize, 0xE5);
                diskImage.write(reinterpret_cast<const char *>(pad.data()), pad.size());
            }
        }

        int blocksWritten = 0;
        int recordsWritten = 0;

        for (int ext = 0; ext < numExtents; ext++) {
            int dirEntryIdx = findFreeDirEntry(diskImage);
            if (dirEntryIdx < 0) {
                diskImage.flush();
                return false;
            }

            int blocksInExtent = std::min(BLOCKS_PER_EXTENT, numBlocks - blocksWritten);
            int recordsInExtent;
            if (ext < numExtents - 1) {
                recordsInExtent = RECORDS_PER_EXTENT;
            } else {
                int remainingRecords = numRecords - recordsWritten;
                recordsInExtent = std::min(RECORDS_PER_EXTENT, remainingRecords);
            }

            size_t dirOffset = DIR_OFFSET + dirEntryIdx * 32;
            std::vector<BYTE> entry(32, 0x00);
            entry[0] = 0;
            std::memcpy(entry.data() + 1, name8.data(), 8);
            std::memcpy(entry.data() + 9, ext3.data(), 3);
            entry[12] = static_cast<BYTE>(ext);
            entry[13] = 0;
            entry[14] = 0;
            entry[15] = static_cast<BYTE>(recordsInExtent);
            for (int j = 0; j < blocksInExtent; j++) {
                entry[16 + j] = blockAlloc[blocksWritten + j];
            }

            diskImage.seekp(dirOffset);
            diskImage.write(reinterpret_cast<const char *>(entry.data()), 32);

            blocksWritten += blocksInExtent;
            recordsWritten += recordsInExtent;
        }

        diskImage.flush();
        return true;
    }

    bool loadCCPFromBinary(const std::filesystem::path &diskPath,
                           const std::filesystem::path &binaryPath,
                           size_t ccpOffsetInBinary,
                           int drive = 0) {
        std::ifstream bin(binaryPath, std::ios::binary);
        if (!bin.is_open())
            return false;

        bin.seekg(0, std::ios::end);
        size_t binSize = bin.tellg();
        if (ccpOffsetInBinary >= binSize)
            return false;

        size_t ccpSize = binSize - ccpOffsetInBinary;
        bin.seekg(ccpOffsetInBinary);

        std::vector<char> ccpData(ccpSize);
        bin.read(ccpData.data(), ccpSize);

        std::fstream img(diskPath, std::ios::in | std::ios::out | std::ios::binary);
        if (!img.is_open())
            return false;

        size_t imgOffset = SECTOR_SIZE;
        img.seekp(imgOffset);
        img.write(ccpData.data(), ccpSize);

        return img.good();
    }

    BYTE Read(WORD address) override {
        Logger *logger = Logger::getLogger();
        std::stringstream ss;
        std::lock_guard lock(disk_mtx);
        BYTE status = 0xFF;
        if (address == CMD_PORT) {
            ss << "<-- floppy status requested. Value is: " << std::hex << (int) lastStatus;
            status = lastStatus;
        } else if (address == DRIVE_SELECT_PORT) {
            BYTE available = drives[selectedDrive].image.is_open() ? 0 : 1;
            ss << "<-- drive " << selectedDrive << " availability: " << (int) available;
            logger->Log(ss.str());
            status = available;
        } else {
            ss << "<-- unknown command (" << std::hex << (int) address << ") requested ??";
        }
        logger->Log(ss.str());
        return status;
    }

    void Write(WORD address, BYTE value) override {
        Logger *logger = Logger::getLogger();
        std::stringstream ss;
        std::lock_guard lock(disk_mtx);
        switch (address) {
            case TRACK_PORT:
                ss << "--> write TRACK_PORT " << std::hex << (int) value;
                logger->Log(ss.str());
                currentTrack = value;
                break;
            case SECTOR_PORT:
                ss << "--> write SECTOR_PORT " << std::hex << (int) value;
                logger->Log(ss.str());
                currentSector = value;
                break;
            case DMA_LOW_PORT:
                ss << "--> write DMA_LOW_PORT " << std::hex << (int) value;
                logger->Log(ss.str());
                dmaAddress = (dmaAddress & 0xFF00) | value;
                break;
            case DMA_HIGH_PORT:
                ss << "--> write DMA_HIGH_PORT " << std::hex << (int) value;
                logger->Log(ss.str());
                dmaAddress = (dmaAddress & 0x00FF) | (static_cast<WORD>(value) << 8);
                break;
            case DRIVE_SELECT_PORT:
                ss << "--> write DRIVE_SELECT_PORT drive=" << std::hex << (int) value;
                logger->Log(ss.str());
                if (value < MAX_DRIVES)
                    selectedDrive = value;
                break;
            case CMD_PORT:
                ss << "--> write CMD_PORT address " << std::hex << (int) value;
                logger->Log(ss.str());
                executeCommand(value);
                break;
        }
    }

    BYTE &operator[](WORD address) override {
        static BYTE dummy = 0;
        return dummy;
    }

private:
    void executeCommand(BYTE command) {
        if (!memory) {
            fprintf(stderr, "DISK ERR: memory not set\n");
            lastStatus = 1;
            return;
        }

        if (currentTrack >= TRACKS || currentSector < 1 || currentSector > SECTORS_PER_TRACK) {
            fprintf(stderr, "DISK ERR: invalid trk=%d sec=%d\n", currentTrack, currentSector);
            lastStatus = 1;
            return;
        }

        size_t offset = (static_cast<size_t>(currentTrack) * SECTORS_PER_TRACK +
                         (currentSector - 1)) * SECTOR_SIZE;

        auto &diskImage = drives[selectedDrive].image;
        if (!diskImage.is_open()) {
            lastStatus = 1;
            return;
        }

        if (memSize < SECTOR_SIZE || dmaAddress > memSize - SECTOR_SIZE) {
            fprintf(stderr, "DISK ERR: DMA 0x%04X overflows %zu-byte memory\n", dmaAddress, memSize);
            lastStatus = 1;
            return;
        }

        Logger *logger = Logger::getLogger();
        std::stringstream ss;
        switch (command) {
            case CMD_READ: {
                ss << "--| CMD_READ drive=" << selectedDrive << " " << int(SECTOR_SIZE) << " bytes with offset "
                   << int(offset) << ": ";
                char buffer[SECTOR_SIZE];
                diskImage.clear();
                diskImage.seekg(offset);
                diskImage.read(buffer, SECTOR_SIZE);
                if (!diskImage) {
                    fprintf(stderr, "DISK READ FAIL at trk=%d sec=%d off=%zu\n", currentTrack, currentSector, offset);
                    lastStatus = 1;
                    return;
                }
                ss << "\n(char) [";
                for (int i = 0; i < SECTOR_SIZE; i++) {
                    memory->Write(dmaAddress + i, static_cast<BYTE>(buffer[i]));
                    ss << static_cast<char>(buffer[i]) << " ";
                }
                ss << "]";
                ss << "\n(hex)  [";
                for (int i = 0; i < SECTOR_SIZE; i++) {
                    ss << std::hex << std::setfill('0') << std::setw(2)
                       << static_cast<int>(static_cast<unsigned char>(buffer[i])) << " ";
                }
                ss << "]";
                lastStatus = 0;
                logger->Log(ss.str());
                break;
            }
            case CMD_WRITE: {
                ss << "--| CMD_WRITE drive=" << selectedDrive << " " << int(SECTOR_SIZE) << " bytes with offset "
                   << int(offset) << ": ";
                char buffer[SECTOR_SIZE];
                ss << "\n(char) [";
                for (int i = 0; i < SECTOR_SIZE; i++) {
                    buffer[i] = static_cast<char>(memory->Read(dmaAddress + i));
                    ss << static_cast<char>(buffer[i]) << " ";
                }
                ss << "]";
                ss << "\n(hex)  [";
                for (int i = 0; i < SECTOR_SIZE; i++) {
                    ss << std::hex << std::setfill('0') << std::setw(2)
                       << static_cast<int>(static_cast<unsigned char>(buffer[i])) << " ";
                }
                ss << "]";
                diskImage.clear();
                diskImage.seekp(offset);
                diskImage.write(buffer, SECTOR_SIZE);
                if (!diskImage) {
                    lastStatus = 1;
                    return;
                }
                diskImage.flush();
                lastStatus = 0;
                logger->Log(ss.str());
                break;
            }
            default:
                lastStatus = 1;
                break;
        }
    }

    static uint8_t findMaxBlock(std::fstream &diskImage) {
        uint8_t maxBlock = 0;
        for (size_t i = 0; i < DIR_ENTRIES; i++) {
            size_t offset = DIR_OFFSET + i * 32;
            diskImage.clear();
            diskImage.seekg(offset);
            char entry[32];
            diskImage.read(entry, 32);
            if ((uint8_t) entry[0] == 0xE5)
                continue;
            for (int block = 16; block < 32; block++) {
                uint8_t b = static_cast<uint8_t>(entry[block]);
                if (b == 0)
                    break;
                if (b > maxBlock)
                    maxBlock = b;
            }
        }
        return maxBlock;
    }

    int countFreeDirEntries(std::fstream &diskImage) {
        int free = 0;
        for (int i = 0; i < DIR_ENTRIES; i++) {
            size_t offset = DIR_OFFSET + i * 32;
            diskImage.clear();
            diskImage.seekg(offset);
            BYTE user;
            diskImage.read(reinterpret_cast<char *>(&user), 1);
            if (user == 0xE5)
                free++;
        }
        return free;
    }

    static std::pair<std::string, std::string> parseCpmName(const std::string &cpmName) {
        std::string name8(8, ' ');
        std::string ext3(3, ' ');
        auto dot = cpmName.find('.');
        if (dot != std::string::npos) {
            std::string rawName = cpmName.substr(0, dot);
            std::string rawExt = cpmName.substr(dot + 1);
            std::copy_n(rawName.begin(), std::min(rawName.size(), size_t(8)), name8.begin());
            std::copy_n(rawExt.begin(), std::min(rawExt.size(), size_t(3)), ext3.begin());
        } else {
            std::copy_n(cpmName.begin(), std::min(cpmName.size(), size_t(8)), name8.begin());
        }
        for (auto &c: name8) c = std::toupper(static_cast<unsigned char>(c));
        for (auto &c: ext3) c = std::toupper(static_cast<unsigned char>(c));
        return {name8, ext3};
    }

    int findFreeDirEntry(std::fstream &diskImage) {
        for (int i = 0; i < DIR_ENTRIES; i++) {
            size_t offset = DIR_OFFSET + i * 32;
            diskImage.clear();
            diskImage.seekg(offset);
            BYTE user;
            diskImage.read(reinterpret_cast<char *>(&user), 1);
            if (user == 0xE5)
                return i;
        }
        return -1;
    }

    BYTE currentTrack = 0;
    BYTE currentSector = 1;
    WORD dmaAddress = 0;
    BYTE lastStatus = 0;
    int selectedDrive = 0;

    Drive drives[MAX_DRIVES];
    Memory<WORD> *memory = nullptr;
    size_t memSize = 0;
    std::mutex disk_mtx;
};

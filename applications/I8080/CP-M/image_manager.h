#pragma once

#include <filesystem>
#include <iostream>
#include "floppy_disk.h"

class ImageManager {
public:
    static constexpr size_t CCP_OFFSET = 0xDC00;

    static bool createImage(const std::filesystem::path &imagePath,
                            const std::filesystem::path &ccpBinPath) {
        if (!FloppyDisk::createEmptyDisk(imagePath)) {
            std::cerr << "Failed to create empty disk image" << std::endl;
            return false;
        }

        FloppyDisk tempDisk;
        if (!tempDisk.loadCCPFromBinary(imagePath, ccpBinPath, CCP_OFFSET)) {
            std::cerr << "Failed to load CCP into image" << std::endl;
            return false;
        }

        std::cout << "Created image: " << imagePath << std::endl;
        return true;
    }

    static bool createDriveImage(const std::filesystem::path &imagePath) {
        if (!FloppyDisk::createEmptyDisk(imagePath)) {
            std::cerr << "Failed to create empty disk image" << std::endl;
            return false;
        }

        std::cout << "Created drive image: " << imagePath << std::endl;
        return true;
    }

    static bool injectFiles(FloppyDisk &disk, const std::vector<std::filesystem::path> &files) {
        for (const auto &hostPath: files) {
            std::string cpmName = hostPath.filename().string();
            if (disk.injectFile(hostPath, cpmName)) {
                std::cout << "Injected: " << cpmName << std::endl;
            } else {
                std::cerr << "Failed to inject: " << hostPath << std::endl;
                return false;
            }
        }
        return true;
    }

    static bool openImage(FloppyDisk &disk,
                          const std::filesystem::path &imagePath,
                          int drive = 0) {
        if (!std::filesystem::exists(imagePath)) {
            std::cerr << "Image not found: " << imagePath << std::endl;
            return false;
        }

        if (!disk.openDisk(imagePath, drive)) {
            std::cerr << "Failed to open image: " << imagePath << std::endl;
            return false;
        }

        return true;
    }
};

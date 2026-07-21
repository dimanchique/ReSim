#include "I8080.h"
#include "memory.h"
#include "bus.h"
#include "keyboard.h"
#include "tty.h"
#include "floppy_disk.h"
#include "cli_parser.h"
#include "image_manager.h"
#include "logger.h"
#include <thread>
#include <atomic>
#include <filesystem>
#include <iostream>

std::atomic<bool> g_running{true};

void keyboard_thread(Keyboard *kbd) {
    while (g_running) {
        if (char input = get_single_key()) {
            kbd->set_input(input);
        } else {
            g_running = false;
            break;
        }
    }
}

int main(int argc, char **argv) {
    CpmConfig config = parseArgs(argc, argv);

    if (config.mode == CpmConfig::Mode::ERROR) {
        std::cerr << config.errorMessage << std::endl;
        printUsage(argv[0]);
        return 0;
    }

    const std::filesystem::path projectRoot = SOURCE_DIR;
    const std::filesystem::path ccpBinPath = projectRoot / "cpm22.bin";

    Memory<WORD> mem(64);
    mem.Reset();

    Bus<WORD> bus;
    Bus<WORD> dataBus;
    Keyboard kbd;
    TTY tty;
    I8080 cpu;
    FloppyDisk disk;

    if (config.mode == CpmConfig::Mode::CREATE_IMAGE) {
        if (!ImageManager::createImage(config.imagePath, ccpBinPath)) {
            return 1;
        }

        if (!disk.openDisk(config.imagePath)) {
            return 1;
        }

        if (!config.injectFiles.empty()) {
            if (!ImageManager::injectFiles(disk, config.injectFiles)) {
                return 1;
            }
        }

        if (config.hasDriveB) {
            if (!ImageManager::createDriveImage(config.driveBPath)) {
                return 1;
            }
        }

        if (config.hasDriveC) {
            if (!ImageManager::createDriveImage(config.driveCPath)) {
                return 1;
            }
        }

        if (config.hasDriveD) {
            if (!ImageManager::createDriveImage(config.driveDPath)) {
                return 1;
            }
        }

        return 0;
    }

    if (!ImageManager::openImage(disk, config.imagePath, 0)) {
        return 1;
    }

    if (config.hasDriveB) {
        if (!ImageManager::openImage(disk, config.driveBPath, 1)) {
            return 1;
        }
    }

    if (config.hasDriveC) {
        if (!ImageManager::openImage(disk, config.driveCPath, 2)) {
            return 1;
        }
    }

    if (config.hasDriveD) {
        if (!ImageManager::openImage(disk, config.driveDPath, 3)) {
            return 1;
        }
    }

    disk.setMemory(mem);

    bus.Attach(&mem, 0x0000, 0xFFFF);
    dataBus.Attach(&kbd, Keyboard::KEYBOARD_STATUS, Keyboard::KEYBOARD_DATA);
    dataBus.Attach(&tty, TTY::TTY_OUTPUT, TTY::TTY_OUTPUT);
    dataBus.Attach(&disk, FloppyDisk::CMD_PORT, FloppyDisk::DRIVE_SELECT_PORT);

    Logger* logger = Logger::getLogger();
    cpu.LoadROM(ccpBinPath.c_str(), mem);
    cpu.SetBusInstance(&bus);
    cpu.SetDataBusInstance(&dataBus);

    U32 cycles = 0;
    std::thread kb_thread(keyboard_thread, &kbd);
    std::thread cpu_thread([&cpu, &cycles]() { cycles = cpu.Run(); });

    while (g_running) {}
    g_running.store(false);
    logger->Stop();
    cpu.Stop();
    kb_thread.join();
    cpu_thread.join();

    return 0;
}

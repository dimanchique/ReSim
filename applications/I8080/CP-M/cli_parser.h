#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

struct CpmConfig {
    enum class Mode {
        CREATE_IMAGE,
        RUN_IMAGE,
        ERROR
    };

    Mode mode = Mode::ERROR;
    std::filesystem::path imagePath;
    std::filesystem::path driveBPath;
    std::filesystem::path driveCPath;
    std::filesystem::path driveDPath;
    bool hasDriveB = false;
    bool hasDriveC = false;
    bool hasDriveD = false;
    std::vector<std::filesystem::path> injectFiles;
    std::string errorMessage;
};

inline CpmConfig parseArgs(int argc, char **argv) {
    CpmConfig config;
    bool hasCreateImage = false;
    bool hasRunImage = false;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "--create-image" && i + 1 < argc) {
            hasCreateImage = true;
            config.imagePath = argv[++i];
            config.mode = CpmConfig::Mode::CREATE_IMAGE;
        } else if (arg == "--image" && i + 1 < argc) {
            hasRunImage = true;
            config.imagePath = argv[++i];
            config.mode = CpmConfig::Mode::RUN_IMAGE;
        } else if (arg == "--drive-b" && i + 1 < argc) {
            config.hasDriveB = true;
            config.driveBPath = argv[++i];
        } else if (arg == "--drive-c" && i + 1 < argc) {
            config.hasDriveC = true;
            config.driveCPath = argv[++i];
        } else if (arg == "--drive-d" && i + 1 < argc) {
            config.hasDriveD = true;
            config.driveDPath = argv[++i];
        } else if (arg == "--inject" && i + 1 < argc) {
            config.injectFiles.emplace_back(argv[++i]);
        } else {
            config.errorMessage = "Unknown argument: " + arg;
            config.mode = CpmConfig::Mode::ERROR;
            return config;
        }
    }

    if (hasCreateImage && hasRunImage) {
        config.errorMessage = "Error: --create-image and --image are mutually exclusive";
        config.mode = CpmConfig::Mode::ERROR;
        return config;
    }

    if (!hasCreateImage && !hasRunImage) {
        config.errorMessage = "no image to load";
        config.mode = CpmConfig::Mode::ERROR;
        return config;
    }

    if (!config.injectFiles.empty() && !hasCreateImage) {
        config.errorMessage = "Error: --inject can only be used with --create-image";
        config.mode = CpmConfig::Mode::ERROR;
        return config;
    }

    return config;
}

inline void printUsage(const char *programName) {
    std::cout << "Usage:\n"
              << "  " << programName
              << " --create-image <path> [--drive-b <path>] [--drive-c <path>] [--drive-d <path>] [--inject <file>...]\n"
              << "  " << programName << " --image <path> [--drive-b <path>] [--drive-c <path>] [--drive-d <path>]\n"
              << "\n"
              << "Options:\n"
              << "  --create-image <path>  Create a new disk image at <path> (drive A:)\n"
              << "  --image <path>         Run an existing disk image from <path> (drive A:)\n"
              << "  --drive-b <path>       Mount drive B: from <path>\n"
              << "  --drive-c <path>       Mount drive C: from <path>\n"
              << "  --drive-d <path>       Mount drive D: from <path>\n"
              << "  --inject <file>        Inject a file into drive A: (repeatable, create mode only)\n";
}

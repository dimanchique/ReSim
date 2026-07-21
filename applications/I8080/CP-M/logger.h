#pragma once

#include "mutex"
#include "memory"
#include "string"
#include "vector"
#include "thread"
#include "atomic"
#include "fstream"
#include "iostream"

#define tmp_path "/tmp/cp-m.log"

class Logger {
public:
    static Logger *getLogger() {
        static std::unique_ptr<Logger> logger = std::make_unique<Logger>();
        return logger.get();
    }

    Logger() {
        fileStream = std::ofstream(tmp_path);
        if (!fileStream.is_open()) {
            std::cerr << "Can't open " tmp_path "\n";
            abort();
        }
        loggerTh = std::thread(&Logger::dumpLogHandle, this);
    }

    virtual ~Logger() {
        if (fileStream.is_open())
            fileStream.close();
    }

    void Log(const std::string log) {
        std::lock_guard _lock(buffMutex);
        buffer.emplace_back(log);
        logsCount++;
    }

    void Stop() {
        shouldRun = false;
    }

private:
    void dumpLogHandle() {
        while (shouldRun) {
            if (logsCount.load()) {
                std::vector<std::string> bufferCopy;
                {
                    std::lock_guard _lock(buffMutex);
                    bufferCopy = buffer;
                    buffer.clear();
                    logsCount.store(0);
                }

                for (std::string &el: bufferCopy) {
                    fileStream << el << "\n";
                }
                fileStream.flush();
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        }
    }

    std::ofstream fileStream;
    std::thread loggerTh;
    std::vector<std::string> buffer;
    std::mutex buffMutex{};
    std::atomic<int> logsCount{0};
    bool shouldRun = true;
};

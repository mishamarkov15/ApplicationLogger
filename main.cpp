#include <iostream>
#include <thread>
#include "library.h"

using namespace message_logger;

const std::string debugKey = "DEBUG";
const std::string infoKey = "INFO";
const std::string warningKey = "WARNING";
const std::string errorKey = "ERROR";
const std::string criticalKey = "CRITICAL";

const std::string exitKey = ":exit";
const std::string changeKey = ":change";

void printHelp() {
    std::cout << "Usage: ./LoggerApplication <file_name> [DEBUG|INFO|WARNING|ERROR|CRITICAL]\n";
    std::cout << "\t- <file_name> - required\n";
    std::cout << "\t- [DEBUG|INFO|WARNING|ERROR|CRITICAL] - optional. default = DEBUG.\n";
}

void printMenu() {
    std::cout << "- Type :exit to exit from program\n";
    std::cout << "- If you want to change default level of logging, please type\n";
    std::cout << ":change [DEBUG|INFO|WARNING|ERROR|CRITICAL]\n";
    std::cout << "- You can write message in two ways:\n";
    std::cout << "INFO: hello, world!\n";
    std::cout << "CRITICAL: This is critical message.\n";
    std::cout << "This is message with default level of logging.\n";
}

FileLogger::MessageLevel parseLevel(const std::string& message, FileLogger::MessageLevel default_value) {
    if (message.find(debugKey) == 0) {
        return FileLogger::MessageLevel::kDebug;
    }
    if (message.find(infoKey) == 0) {
        return FileLogger::MessageLevel::kInfo;
    }
    if (message.find(warningKey) == 0) {
        return FileLogger::MessageLevel::kWarning;
    }
    if (message.find(errorKey) == 0) {
        return FileLogger::MessageLevel::kError;
    }
    if (message.find(criticalKey) == 0) {
        return FileLogger::MessageLevel::kCritical;
    }
    return default_value;
}

std::string clearStringFromLevel(std::string str) {
    std::string message = str;
    if (message.find(debugKey) == 0) {
        message.erase(0, debugKey.size() + 1);
    } else if (message.find(infoKey) == 0) {
        message.erase(0, infoKey.size() + 1);
    } else if (message.find(warningKey) == 0) {
        message.erase(0, warningKey.size() + 1);
    } else if (message.find(errorKey) == 0) {
        message.erase(0, errorKey.size() + 1);
    } else if (message.find(criticalKey) == 0) {
        message.erase(0, criticalKey.size() + 1);
    }
    return message;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printHelp();
        return 1;
    }
    FileLogger::MessageLevel default_level = FileLogger::MessageLevel::kDebug;
    if (argc >= 3) {
        default_level = parseLevel(argv[2], default_level);
    }
    FileLogger ml(argv[1], default_level);

    std::string str;
    printMenu();
    while (std::getline(std::cin, str)) {
        if (str == exitKey) {
            exit(0);
        } else if (str[0] == ':' && str.find(changeKey) == 0) {
            std::string level = str.substr(changeKey.size() + 1);
            default_level = parseLevel(level, default_level);
            if (default_level != ml.getDefaultLevel()) {
                std::cout << "OK. Default level now: " << level << '\n';
                ml.setDefaultLevel(default_level);
            } else {
                std::cout << "ERROR. Unknown level: " << level << '\n';
            }
        } else {
            auto message_level = parseLevel(str, default_level);
            std::thread t([message_level, str, &ml]() {
                ml.logMessage(message_level, clearStringFromLevel(str));
            });
            t.detach();
        }
    }
    return 0;
}

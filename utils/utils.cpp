#include "utils.h"

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
    if (message.find(kDebugKey) == 0) {
        return FileLogger::MessageLevel::kDebug;
    }
    if (message.find(kInfoKey) == 0) {
        return FileLogger::MessageLevel::kInfo;
    }
    if (message.find(kWarningKey) == 0) {
        return FileLogger::MessageLevel::kWarning;
    }
    if (message.find(kErrorKey) == 0) {
        return FileLogger::MessageLevel::kError;
    }
    if (message.find(kCriticalKey) == 0) {
        return FileLogger::MessageLevel::kCritical;
    }
    return default_value;
}

std::string clearStringFromLevel(std::string str) {
    std::string message = str;
    if (message.find(kDebugKey) == 0) {
        message.erase(0, kDebugKey.size() + 1);
    } else if (message.find(kInfoKey) == 0) {
        message.erase(0, kInfoKey.size() + 1);
    } else if (message.find(kWarningKey) == 0) {
        message.erase(0, kWarningKey.size() + 1);
    } else if (message.find(kErrorKey) == 0) {
        message.erase(0, kErrorKey.size() + 1);
    } else if (message.find(kCriticalKey) == 0) {
        message.erase(0, kCriticalKey.size() + 1);
    }
    return message;
}
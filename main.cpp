#include <iostream>
#include <thread>
#include "library.h"
#include "utils/utils.h"

using namespace message_logger;


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
        if (str == kExitKey) {
            exit(0);
        } else if (str[0] == ':' && str.find(kChangeKey) == 0) {
            std::string level = str.substr(kChangeKey.size() + 1);
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

#ifndef LOGGERAPPLICATION_UTILS_H
#define LOGGERAPPLICATION_UTILS_H

#include <iostream>
#include <string>
#include "library.h"

using namespace message_logger;

const std::string kDebugKey = "DEBUG";
const std::string kInfoKey = "INFO";
const std::string kWarningKey = "WARNING";
const std::string kErrorKey = "ERROR";
const std::string kCriticalKey = "CRITICAL";

const std::string kExitKey = ":exit";
const std::string kChangeKey = ":change";

void printHelp();

void printMenu();

FileLogger::MessageLevel parseLevel(const std::string& message, FileLogger::MessageLevel default_value);

std::string clearStringFromLevel(std::string str);


#endif //LOGGERAPPLICATION_UTILS_H

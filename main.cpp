#include <iostream>
#include "library.h"

int main() {
    message_logger::FileLogger ml("../out.txt", message_logger::FileLogger::MessageLevel::kDebug);
    ml.logMessage(message_logger::FileLogger::MessageLevel::kDebug, "Hello, world!");
    return 0;
}

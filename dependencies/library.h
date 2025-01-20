#ifndef MESSAGELOGGER_LIBRARY_H
#define MESSAGELOGGER_LIBRARY_H

#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <ctime>

namespace message_logger {
    class FileLogger {
    public:
        enum class MessageLevel {
            kDebug,
            kInfo,
            kWarning,
            kError,
            kCritical
        };

        static const std::vector<std::string> levels;

        /**
         * Creates FileLogger instance.
         * @param file_name[in]: path to the file in which we want store records.
         * @param level[in]: default level of records. Messages with a lower level will not be logged.
         */
        FileLogger(std::string file_name, MessageLevel default_level);

        /**
         * Sets default level for logging. Messages with a lower level will not be logged.
         * @param level[in]: default level of records.
         */
        void setDefaultLevel(MessageLevel level);

        /**
         * Gets default level for logging. Just getter method.
         * @return default_level.
         */
        MessageLevel getDefaultLevel() const noexcept;

        void logMessage(MessageLevel level, const std::string& message);
    private:
        std::string file_name;
        MessageLevel default_level;
    };
}


#endif //MESSAGELOGGER_LIBRARY_H

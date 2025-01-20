#include "../include/library.h"

#include <iostream>

namespace message_logger {
    const std::vector<std::string> FileLogger::levels = {
            "DEBUG",
            "INFO",
            "WARNING",
            "ERROR",
            "CRITICAL"
    };

    FileLogger::FileLogger(std::string file_name, MessageLevel default_level) :
            m_file_name(std::move(file_name)),
            m_default_level(default_level) {

    }

    void FileLogger::setDefaultLevel(MessageLevel level) {
        std::lock_guard<std::mutex> lg(m_mutex);
        m_default_level = level;
    }

    FileLogger::MessageLevel FileLogger::getDefaultLevel() const noexcept {
        return m_default_level;
    }

    void FileLogger::logMessage(FileLogger::MessageLevel level, const std::string &message) {
        if (level < m_default_level) return;
        std::ofstream fout(m_file_name, std::ios::app | std::ios::out);
        if (!fout.is_open()) {
            std::ostringstream os;
            os << "File " << m_file_name << " was not open";
            throw std::runtime_error(os.str());
        }
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);

        std::lock_guard<std::mutex> lg(m_mutex);
        fout << levels[static_cast<int>(level)];
        fout << " [" << std::put_time(&tm, "%d.%m.%Y %H:%M:%S") << "]: ";
        fout << message << '\n';
        fout.close();
    }
}


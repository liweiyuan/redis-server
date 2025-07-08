#pragma once
#include <ctime>
#include <fstream>
#include <mutex>
#include <string>

enum class LogLevel { DEBUG, INFO, WARN, ERROR };

class Logger {
public:
  static void init(const std::string &name, const std::string &filename,
                   LogLevel level);
  static void log(LogLevel level, const std::string &msg);
  static void debug(const std::string &msg);
  static void info(const std::string &msg);
  static void warn(const std::string &msg);
  static void error(const std::string &msg);
  static bool shouldLog(LogLevel level);

private:
  static std::string levelToString(LogLevel level);
  static std::ofstream log_file;
  static std::string logger_name;
  static LogLevel log_level;
  static std::mutex log_mutex;
};

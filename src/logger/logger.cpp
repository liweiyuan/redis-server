#include "logger.h"
#include <iomanip>

std::ofstream Logger::log_file;
std::string Logger::logger_name = "";
LogLevel Logger::log_level = LogLevel::INFO;
std::mutex Logger::log_mutex;

void Logger::init(const std::string &name, const std::string &filename,
                  LogLevel level) {
  std::lock_guard<std::mutex> lock(log_mutex);
  logger_name = name;
  log_level = level;
  if (log_file.is_open())
    log_file.close();
  log_file.open(filename, std::ios::app);
}

bool Logger::shouldLog(LogLevel level) {
  return static_cast<int>(level) >= static_cast<int>(log_level);
}

std::string Logger::levelToString(LogLevel level) {
  switch (level) {
  case LogLevel::DEBUG:
    return "DEBUG";
  case LogLevel::INFO:
    return "INFO";
  case LogLevel::WARN:
    return "WARN";
  case LogLevel::ERROR:
    return "ERROR";
  default:
    return "INFO";
  }
}

void Logger::log(LogLevel level, const std::string &msg) {
  if (!shouldLog(level))
    return;
  std::lock_guard<std::mutex> lock(log_mutex);
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  if (log_file.is_open()) {
    log_file << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] ["
             << logger_name << "] [" << levelToString(level) << "] " << msg
             << std::endl;
  }
}

void Logger::debug(const std::string &msg) { log(LogLevel::DEBUG, msg); }
void Logger::info(const std::string &msg) { log(LogLevel::INFO, msg); }
void Logger::warn(const std::string &msg) { log(LogLevel::WARN, msg); }
void Logger::error(const std::string &msg) { log(LogLevel::ERROR, msg); }

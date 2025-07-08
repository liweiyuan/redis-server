#include "config/config.h"
#include "logger/logger.h"
#include "network/network.h"
#include <iostream>

int main() {
  Config config;
  if (!config.load("redis.conf")) {
    std::cerr << "Failed to load config file redis.conf, using default config."
              << std::endl;
  }
  // 日志级别字符串转LogLevel
  LogLevel level = LogLevel::INFO;
  std::string lvl = config.getLogLevel();
  if (lvl == "debug")
    level = LogLevel::DEBUG;
  else if (lvl == "info")
    level = LogLevel::INFO;
  else if (lvl == "warn")
    level = LogLevel::WARN;
  else if (lvl == "error")
    level = LogLevel::ERROR;
  Logger::init(config.getLogName(), config.getLogFile(), level);
  Logger::info("Server starting...");
  Network network;
  network.start();
  return 0;
}
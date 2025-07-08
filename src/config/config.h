#pragma once
#include <string>

class Config {
public:
  bool load(const std::string &filename);
  int getPort() const;
  int getMaxConnections() const;
  std::string getLogLevel() const;
  std::string getLogFile() const;
  std::string getLogName() const;

private:
  int port = 6379;
  int max_connections = 1000;
  std::string log_level = "info";
  std::string log_file = "redis-server.log";
  std::string log_name = "redis-server";
};

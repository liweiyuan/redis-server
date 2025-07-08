#include "config.h"
#include <algorithm>
#include <fstream>

// 简单ini风格配置解析
bool Config::load(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open())
    return false;
  std::string line;
  while (std::getline(file, line)) {
    line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
    if (line.empty() || line[0] == '#')
      continue;
    auto pos = line.find('=');
    if (pos == std::string::npos)
      continue;
    std::string key = line.substr(0, pos);
    std::string value = line.substr(pos + 1);
    if (key == "port")
      port = std::stoi(value);
    else if (key == "max_connections")
      max_connections = std::stoi(value);
    else if (key == "log_level")
      log_level = value;
    else if (key == "log_file")
      log_file = value;
    else if (key == "log_name")
      log_name = value;
  }
  return true;
}
int Config::getPort() const { return port; }
int Config::getMaxConnections() const { return max_connections; }
std::string Config::getLogLevel() const { return log_level; }
std::string Config::getLogFile() const { return log_file; }
std::string Config::getLogName() const { return log_name; }

#include "command.h"
#include "storage/storage.h"
#include <algorithm>
#include <sstream>

std::vector<std::string> parse_request(const char *buffer, int length) {
  std::vector<std::string> command_parts;
  if (buffer[0] != '*') {
    std::string request(buffer, length);
    std::stringstream ss(request);
    std::string part;
    while (ss >> part) {
      command_parts.push_back(part);
    }
    return command_parts;
  }

  std::stringstream ss(std::string(buffer, length));
  std::string line;

  std::getline(ss, line);

  while (std::getline(ss, line)) {
    if (line.rfind('$', 0) == 0) {
      if (std::getline(ss, line)) {
        if (!line.empty() && line.back() == '\r') {
          line.pop_back();
        }
        command_parts.push_back(line);
      }
    }
  }
  return command_parts;
}

std::string GetCommand::execute(const std::vector<std::string> &args) {
  if (args.size() != 1) {
    return "-ERR wrong number of arguments for 'get' command\r\n";
  }
  if (Storage::getInstance().has(args[0])) {
    std::string value = Storage::getInstance().get(args[0]);
    return "$" + std::to_string(value.length()) + "\r\n" + value + "\r\n";
  } else {
    return "$-1\r\n";
  }
}

std::string SetCommand::execute(const std::vector<std::string> &args) {
  if (args.size() != 2) {
    return "-ERR wrong number of arguments for 'set' command\r\n";
  }
  Storage::getInstance().set(args[0], args[1]);
  return "+OK\r\n";
}

CommandRegistry::CommandRegistry() {
  commands["GET"] = std::make_shared<GetCommand>();
  commands["SET"] = std::make_shared<SetCommand>();
}

std::shared_ptr<Command> CommandRegistry::getCommand(const std::string &name) {
  std::string upper_name = name;
  std::transform(upper_name.begin(), upper_name.end(), upper_name.begin(),
                 ::toupper);
  auto it = commands.find(upper_name);
  if (it != commands.end()) {
    return it->second;
  }
  return nullptr;
}

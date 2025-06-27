#include "command.h"
#include "storage.h"
#include <sstream>
#include <algorithm>

std::vector<std::string> parse_request(const char* buffer, int length) {
    std::vector<std::string> command_parts;
    if (buffer[0] != '*') {
        std::string request(buffer, length);
        std::stringstream ss(request);
        std::string part;
        while(ss >> part) {
            command_parts.push_back(part);
        }
        return command_parts;
    }

    std::stringstream ss(std::string(buffer, length));
    std::string line;
    
    std::getline(ss, line); 

    while(std::getline(ss, line)) {
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

std::string execute_command(const std::vector<std::string>& command_parts) {
    if (command_parts.empty()) {
        return "-ERR Invalid command\r\n";
    }

    std::string command = command_parts[0];
    std::transform(command.begin(), command.end(), command.begin(), ::toupper);

    if (command == "SET" && command_parts.size() == 3) {
        Storage::getInstance().set(command_parts[1], command_parts[2]);
        return "+OK\r\n";
    } else if (command == "GET" && command_parts.size() == 2) {
        if (Storage::getInstance().has(command_parts[1])) {
            std::string value = Storage::getInstance().get(command_parts[1]);
            return "$" + std::to_string(value.length()) + "\r\n" + value + "\r\n";
        } else {
            return "$-1\r\n";
        }
    }
    else {
        return "-ERR unknown or invalid command for the number of arguments\r\n";
    }
}
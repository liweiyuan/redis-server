#ifndef REDIS_SERVER_COMMAND_H
#define REDIS_SERVER_COMMAND_H

#include <vector>
#include <string>

std::vector<std::string> parse_request(const char* buffer, int length);
std::string execute_command(const std::vector<std::string>& command_parts);

#endif //REDIS_SERVER_COMMAND_H
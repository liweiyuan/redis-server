#ifndef REDIS_SERVER_COMMAND_H
#define REDIS_SERVER_COMMAND_H

#include <vector>
#include <string>
#include <map>
#include <memory>

// Forward declaration
class Storage;

class Command {
public:
    virtual ~Command() = default;
    virtual std::string execute(const std::vector<std::string>& args) = 0;
};

class GetCommand : public Command {
public:
    std::string execute(const std::vector<std::string>& args) override;
};

class SetCommand : public Command {
public:
    std::string execute(const std::vector<std::string>& args) override;
};

class CommandRegistry {
public:
    CommandRegistry();
    std::shared_ptr<Command> getCommand(const std::string& name);
private:
    std::map<std::string, std::shared_ptr<Command>> commands;
};

std::vector<std::string> parse_request(const char* buffer, int length);

#endif //REDIS_SERVER_COMMAND_H

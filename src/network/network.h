#ifndef REDIS_SERVER_NETWORK_H
#define REDIS_SERVER_NETWORK_H

#include "command/command.h"

class Network {
public:
    void start();
private:
    CommandRegistry command_registry;
};

#endif //REDIS_SERVER_NETWORK_H

#include "network.h"
#include "command/command.h"
#include <iostream>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

// The handle_client function now needs access to the CommandRegistry.
// We can pass it as a parameter.
void handle_client(int client_socket, CommandRegistry& registry) {
    char buffer[1024] = {0};
    while (true) {
        int bytes_received = read(client_socket, buffer, 1024);
        if (bytes_received <= 0) {
            if (bytes_received < 0) {
                perror("read");
            }
            std::cerr << "Client disconnected." << std::endl;
            close(client_socket);
            return;
        }

        std::vector<std::string> command_parts = parse_request(buffer, bytes_received);
        std::string response;

        if (command_parts.empty()) {
            response = "-ERR Invalid command\r\n";
        } else {
            std::string command_name = command_parts[0];
            auto command = registry.getCommand(command_name);
            if (command) {
                command_parts.erase(command_parts.begin()); // Remove command name, pass only args
                response = command->execute(command_parts);
            } else {
                response = "-ERR unknown command '" + command_name + "'\r\n";
            }
        }

        send(client_socket, response.c_str(), response.length(), 0);
        memset(buffer, 0, sizeof(buffer));
    }
}

void Network::start() {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(6379);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0) { 
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port 6379..." << std::endl;

    while (true) {
        int client_socket;
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        std::cout << "New client connected." << std::endl;
        // Pass the command_registry to the handler thread
        std::thread(handle_client, client_socket, std::ref(command_registry)).detach();
    }
}

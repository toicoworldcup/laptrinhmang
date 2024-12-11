#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_CLIENTS 32
#define COMMAND_PORT 5555

std::mutex mtx; // Ð? b?o v? stdout và các thao tác d?ng b? khác

void handle_client(int command_socket) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_received = recv(command_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received <= 0) {
            std::cout << "Client disconnected.\n";
            close(command_socket);
            break;
        }

        std::string command(buffer);
        if (command.starts_with("GET ")) {
            // Parse command
            size_t pos = command.find(' ', 4);
            if (pos == std::string::npos) {
                send(command_socket, "INVALID COMMAND\n", 17, 0);
                continue;
            }
            std::string filename = command.substr(4, pos - 4);
            int data_port = std::stoi(command.substr(pos + 1));

            // Create a new socket for data transfer
            int data_socket = socket(AF_INET, SOCK_STREAM, 0);
            sockaddr_in data_addr{};
            data_addr.sin_family = AF_INET;
            data_addr.sin_port = htons(data_port);
            data_addr.sin_addr.s_addr = INADDR_ANY;

            if (bind(data_socket, (sockaddr*)&data_addr, sizeof(data_addr)) < 0) {
                send(command_socket, "ERROR\n", 6, 0);
                close(data_socket);
                continue;
            }

            listen(data_socket, 1);
            std::cout << "Listening for data connection on port " << data_port << "\n";

            int client_data_socket = accept(data_socket, nullptr, nullptr);
            if (client_data_socket < 0) {
                send(command_socket, "ERROR\n", 6, 0);
                close(data_socket);
                continue;
            }

            // Open and send file
            std::ifstream file(filename, std::ios::binary);
            if (!file.is_open()) {
                send(command_socket, "ERROR\n", 6, 0);
                close(client_data_socket);
                close(data_socket);
                continue;
            }

            char file_buffer[1024];
            while (file.read(file_buffer, sizeof(file_buffer))) {
                send(client_data_socket, file_buffer, file.gcount(), 0);
            }
            file.close();

            // Send DONE message
            send(command_socket, "DONE\n", 5, 0);
            close(client_data_socket);
            close(data_socket);

        } else if (command == "QUIT") {
            send(command_socket, "GOODBYE\n", 8, 0);
            close(command_socket);
            break;

        } else {
            send(command_socket, "INVALID COMMAND\n", 17, 0);
        }
    }
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Failed to create socket.\n";
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(COMMAND_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket.\n";
        return 1;
    }

    if (listen(server_socket, MAX_CLIENTS) < 0) {
        std::cerr << "Failed to listen on socket.\n";
        return 1;
    }

    std::cout << "Server listening on port " << COMMAND_PORT << "\n";

    std::vector<std::thread> client_threads;
    while (true) {
        int client_socket = accept(server_socket, nullptr, nullptr);
        if (client_socket < 0) {
            std::cerr << "Failed to accept connection.\n";
            continue;
        }

        std::cout << "New client connected.\n";
        client_threads.emplace_back(handle_client, client_socket);

        // Cleanup threads that have finished
        for (auto it = client_threads.begin(); it != client_threads.end();) {
            if (it->joinable()) {
                it->join();
                it = client_threads.erase(it);
            } else {
                ++it;
            }
        }
    }

    // Cleanup before exiting
    for (auto& t : client_threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    close(server_socket);
    return 0;
}


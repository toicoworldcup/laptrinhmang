#include <iostream>
#include <winsock2.h>
#include <fstream>

#pragma comment(lib, "ws2_32.lib") 

const int COMMAND_PORT = 5555;

void handleClient(SOCKET commandSocket) {
    char buffer[1024];
    int recvLen = recv(commandSocket, buffer, sizeof(buffer), 0);
    if (recvLen <= 0) {
        std::cerr << "Connection lost.\n";
        return;
    }

    buffer[recvLen] = '\0';
    std::cout << "Received: " << buffer << "\n";

    if (strncmp(buffer, "GET ", 4) == 0) {
        char filename[256];
        int port;
        if (sscanf(buffer, "GET %s %d", filename, &port) == 2) {
            std::cout << "File: " << filename << ", Port: " << port << "\n";
            SOCKET dataSocket = socket(AF_INET, SOCK_STREAM, 0);
            sockaddr_in dataAddr;
            dataAddr.sin_family = AF_INET;
            dataAddr.sin_port = htons(port);
            dataAddr.sin_addr.s_addr = INADDR_ANY;
            bind(dataSocket, (sockaddr*)&dataAddr, sizeof(dataAddr));
            listen(dataSocket, 1);
            send(commandSocket, "READY\n", 6, 0);
            SOCKET clientDataSocket = accept(dataSocket, nullptr, nullptr);
            std::ifstream file(filename, std::ios::binary);
            if (file.is_open()) {
                char fileBuffer[1024];
                while (!file.eof()) {
                    file.read(fileBuffer, sizeof(fileBuffer));
                    send(clientDataSocket, fileBuffer, file.gcount(), 0);
                }
                file.close();
            }

            send(commandSocket, "DONE\n", 5, 0);
            closesocket(clientDataSocket);
            closesocket(dataSocket);
        } else {
            send(commandSocket, "INVALID COMMAND\n", 17, 0);
        }
    } else if (strncmp(buffer, "QUIT", 4) == 0) {
        send(commandSocket, "BYE\n", 4, 0);
    } else {
        send(commandSocket, "INVALID COMMAND\n", 17, 0);
    }
}
int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(COMMAND_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 5);
    std::cout << "Server listening on port " << COMMAND_PORT << "\n";
    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        std::cout << "Client connected.\n";
        handleClient(clientSocket);
        closesocket(clientSocket);
    }
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}

#include <iostream>
#include <winsock2.h>
#include <string>
#include <fstream>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

void downloadFile(SOCKET dataSock, const string& filename) {
    char buffer[1024];
    int bytesReceived;
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    while ((bytesReceived = recv(dataSock, buffer, sizeof(buffer), 0)) > 0) {
        outFile.write(buffer, bytesReceived);
    }
    cout << "File " << filename << " downloaded successfully." << endl;
    outFile.close();
}
int main() {
    WSADATA wsaData;
    SOCKET sock, dataSock;
    sockaddr_in serverAddr, dataAddr;
    string command, filename;
    int port;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Winsock initialization failed" << endl;
        return 1;
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        cout << "Socket creation failed" << endl;
        WSACleanup();
        return 1;
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555); 
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Connection failed" << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    cout << "Enter command (e.g., GET file.txt 5556): ";
    getline(cin, command);
    send(sock, command.c_str(), command.length(), 0);
    char buffer[1024];
    int recvSize = recv(sock, buffer, sizeof(buffer), 0);
    buffer[recvSize] = '\0';
    cout << "Server response: " << buffer << endl;
    if (recvSize > 0 && string(buffer).find("OK") != string::npos) {
        string response(buffer);
        size_t pos = response.find("port ");
        if (pos != string::npos) {
            port = stoi(response.substr(pos + 5));
            dataSock = socket(AF_INET, SOCK_STREAM, 0);
            if (dataSock == INVALID_SOCKET) {
                cout << "Data socket creation failed" << endl;
                closesocket(sock);
                WSACleanup();
                return 1;
            }
            dataAddr.sin_family = AF_INET;
            dataAddr.sin_port = htons(port);
            dataAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
            if (connect(dataSock, (struct sockaddr*)&dataAddr, sizeof(dataAddr)) == SOCKET_ERROR) {
                cout << "Data connection failed" << endl;
                closesocket(sock);
                closesocket(dataSock);
                WSACleanup();
                return 1;
            }
            cout << "Receiving file..." << endl;
            downloadFile(dataSock, filename);
            closesocket(dataSock);
        }
    }
    closesocket(sock);
    WSACleanup();
    return 0;
}

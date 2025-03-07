#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "CatNet.hpp"

#define PORT 25565

int main()
{
    CatNet::init();

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket == -1)
    {
        std::cerr << "Failed to create socket\n";
        return -1;
    }

    sockaddr_in address = {};

    address.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr.s_addr);
    address.sin_port = htons(PORT);

    if (connect(clientSocket, (sockaddr*) &address, sizeof(sockaddr)) == -1)
    {
        std::cerr << "Failed to connect to server on port " << PORT << " is the server online?\n";
        return -1;
    }

    Buffer buffer = SBUsernamePacket::encode(SBUsernamePacket("cteezy"));

    int sentBytes = send(clientSocket, buffer.data(), buffer.size(), 0);
    std::cout << "Sent bytes: " << sentBytes << '\n';

    close(clientSocket);
}
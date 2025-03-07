#include <iostream>
#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <poll.h>
#include <vector>
#include <unistd.h>

#include "CatNet.hpp"

#define PORT 25565

int main()
{
    CatNet::init();

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1)
    {
        std::cerr << "Unable to create server socket\n";
        return -1;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr.s_addr);
    address.sin_port = htons(PORT);

    if (bind(serverSocket, (sockaddr *)&address, sizeof(sockaddr_in)) == -1)
    {
        std::cerr << "Failed to bind on port " << PORT << "\n";
        return -1;
    }

    if (listen(serverSocket, 3) == -1)
    {
        std::cerr << "Failed to start listening on port " << PORT << "\n";
        return -1;
    }

    if (fcntl(serverSocket, F_SETFL, O_NONBLOCK) == -1)
    {
        std::cerr << "Unable to set socket to non-blocking!\n";
        return -1;
    }

    std::cout << "Server listening on port " << PORT << '\n';

    auto packetHandler = [](unsigned int packetType, void* packetData)
    {
        switch ((PacketType::Server) packetType)
        {
            case PacketType::Server::USERNAME:
            {
                SBUsernamePacket* usernamePacket = (SBUsernamePacket*) packetData;
                std::cout<< usernamePacket->username() << '\n';
                delete usernamePacket;
                break;
            }
        }
    };

    std::vector<pollfd> pollfds;
    std::vector<PacketBuilder> packetBuilders;
    std::vector<std::string> usernames;

    pollfds.push_back({serverSocket, POLLIN, 0});
    packetBuilders.push_back(PacketBuilder(nullptr, nullptr));
    usernames.push_back("");

    while (true)
    {
        if (poll(pollfds.data(), pollfds.size(), 1) > 0)
        {
            if (pollfds[0].revents & POLLIN)
            {
                int clientSocket = accept(serverSocket, nullptr, nullptr);

                if (clientSocket == -1)
                {
                    std::cerr << "Failed to accept connection\n";
                    continue;
                }

                if (fcntl(clientSocket, F_SETFL, O_NONBLOCK) == -1)
                {
                    std::cerr << "Failed to set client to non-blocking, closing connection.\n";
                    close(clientSocket);
                    continue;
                }

                std::cout << "Accepted new connection\n";

                pollfds.push_back({ clientSocket, POLLIN, 0 });
                packetBuilders.push_back(std::move(PacketBuilder(CatNet::Registry::Server::getPacketDecoder, packetHandler)));
            }

            for (int i = 1; i < pollfds.size(); i++)
            {
                pollfd pollResult = pollfds[i];

                if (pollResult.revents & POLLIN)
                {
                    PacketBuilder& packetBuilder = packetBuilders[i];
                    packetBuilder.read(pollResult.fd);
                }
            }
        }
    }
}
#pragma once

#include <string>
#include "IPEndpoint.hpp"

class TCPSocket
{
    public:

    TCPSocket(int fileDescriptor);

    int connect(const IPEndpoint& address);
    int bind(const IPEndpoint& address);
    int listen();
    int receieve(char* buffer, size_t bufferSize);
    int send(char* buffer, size_t bufferSize);
    int setBlocking(bool isBlocking);
    int close();
    TCPSocket accept();

    static TCPSocket Create();

    private:

    //The file descriptor that is given by the OS when doing socket()
    int m_fd;

};
#include "TCPSocket.hpp"

#include <sys/socket.h>
#include <errno.h>
#include <iostream>
#include <exception>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

TCPSocket::TCPSocket(int fileDescriptor)
    : m_fd(fileDescriptor)
{
    
}

int TCPSocket::connect(const IPEndpoint& endpoint)
{
    sockaddr_in connectionAddress = {};
    connectionAddress.sin_family = AF_INET;
    inet_pton(AF_INET, endpoint.getAddress().c_str(), &connectionAddress);
    connectionAddress.sin_port = htons(endpoint.getPort());
    return ::connect(m_fd, (sockaddr*) &connectionAddress, sizeof(sockaddr));
}

int TCPSocket::bind(const IPEndpoint& endpoint)
{
    sockaddr_in socketAddress = {};
    socketAddress.sin_family = AF_INET;
    inet_pton(AF_INET, endpoint.getAddress().c_str(), &socketAddress.sin_addr.s_addr);
    socketAddress.sin_port = htons(endpoint.getPort());
    return ::bind(m_fd, (sockaddr*) &socketAddress, sizeof(sockaddr));
}

int TCPSocket::listen()
{
    return ::listen(m_fd, 5);
}

TCPSocket TCPSocket::accept()
{
    return TCPSocket(::accept(m_fd, nullptr, nullptr));
}

int TCPSocket::receieve(char *buffer, size_t bufferSize)
{
    return ::recv(m_fd, buffer, bufferSize, 0);
}

int TCPSocket::send(char *buffer, size_t bufferSize)
{
    return ::send(m_fd, buffer, bufferSize, 0);
}

int TCPSocket::setBlocking(bool isBlocking)
{
    return fcntl(m_fd, F_SETFL, isBlocking ? ~O_NONBLOCK : O_NONBLOCK);
}

int TCPSocket::close()
{
    ::close(m_fd);
}

TCPSocket TCPSocket::Create()
{
    int socketHandle = ::socket(AF_INET, SOCK_STREAM, 0);
    
    if (socketHandle == -1)
    {
        throw std::runtime_error("Unable to create socket, error reads `" + std::string(strerror(errno)) + "`.");
    }

    return TCPSocket(socketHandle);
}
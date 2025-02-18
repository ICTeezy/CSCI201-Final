#include "IPEndpoint.hpp"

#include <arpa/inet.h>
#include <stdexcept>

IPEndpoint::IPEndpoint(std::string address, unsigned short port)
    : m_address(address), m_port(port)
{
    if (inet_pton(AF_INET, address.c_str(), nullptr) != 1)
    {
        throw std::invalid_argument("IP: `" + address + "` is not a valid IPv4 address!");
    }
}

unsigned short IPEndpoint::getPort() const
{
    return m_port;
}

std::string IPEndpoint::getAddress() const
{
    return m_address;
}
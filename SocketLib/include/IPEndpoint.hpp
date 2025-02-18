#pragma once

#include <arpa/inet.h>
#include <string>

class IPEndpoint
{

    public:

    IPEndpoint(std::string address, unsigned short port);
    unsigned short getPort() const;
    std::string getAddress() const;

    private:

    std::string    m_address;
    unsigned short m_port;

};
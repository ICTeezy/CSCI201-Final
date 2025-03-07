#include "buffer/BufferView.hpp"

#include <cstring>
#include <arpa/inet.h>
#include <iostream>

BufferView::BufferView(const char *buffer, unsigned int limit)
    : m_readPosition(0), m_limit(limit), m_buffer(buffer)
{
}

int BufferView::readInt()
{
    int x;

    if (m_readPosition + sizeof(int) <= m_limit)
    {
        std::memcpy(&x, m_buffer + m_readPosition, sizeof(int));
        x = ntohl(x);
        m_readPosition += sizeof(int);
    }

    return x;
}

std::string BufferView::readString()
{
    unsigned int stringLength = readInt();

    if (m_readPosition + stringLength <= m_limit)
    {
        m_readPosition += stringLength;
        return std::string((char *)m_buffer, stringLength);
    }

    return std::string();
}

BufferView &BufferView::operator>>(int &x)
{
    x = readInt();
    return *this;
}
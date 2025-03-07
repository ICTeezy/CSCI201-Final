#pragma once

#include <cstdint>
#include <string>

class BufferView
{

public:
    BufferView(const char *buffer, unsigned int limit);

    int readInt();
    std::string readString();

    BufferView &operator>>(int &);

private:
    unsigned int m_readPosition;
    const char *m_buffer;
    const unsigned int m_limit;
};
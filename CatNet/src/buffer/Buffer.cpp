#include "buffer/Buffer.hpp"

#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>

#include "buffer/Buffer.hpp"

Buffer::Buffer(unsigned int bufferCapacity)
    : m_capacity(bufferCapacity), m_buffer(new char[bufferCapacity]), m_writeIndex(0)
{
    std::memset(m_buffer, 0, m_capacity);
}

Buffer::~Buffer()
{
    delete[] m_buffer;
}

int Buffer::read(size_t fileDescriptor) noexcept
{
    int readBytes = ::read(fileDescriptor, m_buffer + m_writeIndex, m_capacity);

    if (readBytes > 0)
    {
        m_writeIndex += readBytes;
    }

    return readBytes;
}

void Buffer::writeInt(int data)
{
    data = htonl(data);
    std::memcpy(m_buffer + m_writeIndex, &data, sizeof(int));
    m_writeIndex += sizeof(int);
}

void Buffer::writeString(const std::string &string)
{
    unsigned int stringLength = string.length();
    *this << stringLength;
    std::memcpy(m_buffer + m_writeIndex, string.c_str(), stringLength);
    m_writeIndex += stringLength;
}

Buffer &Buffer::operator<<(int data)
{
    this->writeInt(data);
    return *this;
}

Buffer &Buffer::operator<<(std::string string)
{
    this->writeString(string);
    return *this;
}

BufferView Buffer::view() const
{
    return BufferView(m_buffer, m_writeIndex);
}

char *Buffer::data()
{
    return m_buffer;
}

unsigned int Buffer::capacity() const
{
    return m_capacity;
}

unsigned int Buffer::size() const
{
    return m_writeIndex;
}

Buffer Buffer::allocatePrefixed(unsigned int packetSize, unsigned int packetType)
{
    Buffer buffer(sizeof(unsigned int) + sizeof(unsigned int) + packetSize);
    buffer << packetSize << packetType;
    return buffer;
}
#pragma once

#include "BufferView.hpp"

#include <memory>
#include <cstdint>
#include <string>

class Buffer
{

public:
    Buffer(unsigned int bufferCapacity);
    ~Buffer();

    int read(size_t fileDescriptor) noexcept;

    void writeInt(int data);
    void writeString(const std::string &string);

    Buffer &operator<<(int data);
    Buffer &operator<<(std::string string);

    BufferView view() const;
    char* data();

    unsigned int capacity() const;
    unsigned int size() const;

    static Buffer allocatePrefixed(unsigned int packetSize, unsigned int packetType);

private:
    char* m_buffer;
    unsigned int m_writeIndex;
    unsigned int m_capacity;
};
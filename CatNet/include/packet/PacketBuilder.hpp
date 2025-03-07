#pragma once

#include "buffer/Buffer.hpp"
#include "packet/PacketType.hpp"

#include <functional>

using DecoderLookupFunction = std::function<std::function<void*(Buffer&)>(int packetType)>;
using PacketHandler = std::function<void(unsigned int, void*)>;

class PacketBuilder
{
    enum ProcessingState
    {
        PACKET_SIZE,
        PACKET_CONTENT
    };

public:

    PacketBuilder(DecoderLookupFunction decoderLookupFunction, PacketHandler packetHandler);
    int read(int fileDescriptor);

private:
    Buffer m_buffer;
    ProcessingState m_processingState;
    DecoderLookupFunction m_decoderLookupFunction;
    PacketHandler m_packetHandler;
};
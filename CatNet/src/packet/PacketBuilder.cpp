#include "packet/PacketBuilder.hpp"
#include "buffer/BufferView.hpp"

#include <unistd.h>
#include <iostream>

PacketBuilder::PacketBuilder(DecoderLookupFunction decoderLookupFunction, PacketHandler packetHandler)
    : m_buffer(Buffer(4)), 
    m_processingState(PACKET_SIZE), 
    m_decoderLookupFunction(decoderLookupFunction),
    m_packetHandler(packetHandler)
{
}

int PacketBuilder::read(int fileDescriptor)
{
    int bytesRead = m_buffer.read(fileDescriptor);

    if (m_buffer.size() == m_buffer.capacity())
    {
        if (m_processingState == PACKET_SIZE)
        {
            BufferView view = m_buffer.view();
            unsigned int packetSize = view.readInt();

            // TODO: Handle max packet size.

            m_buffer = Buffer(packetSize);
        }
        else // PACKET_CONTENT
        {
            BufferView view = m_buffer.view();
            unsigned int packetType = view.readInt();

            auto decoder = m_decoderLookupFunction(packetType);
            
            if (decoder == nullptr)
            {
                std::cout << "Invalid packet (" << packetType << ")\n";
            }
            else
            {
                auto packet = decoder(m_buffer);
                m_packetHandler(packetType, packet);
            }
        }
    }

    return bytesRead;
}
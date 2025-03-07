#pragma once

#include "PacketType.hpp"
#include "PacketBuilder.hpp"

#include <functional>

using PacketDecoder = std::function<void*(Buffer &)>;

namespace CatNet::Registry
{
    namespace Server
    {
        PacketDecoder getPacketDecoder(int packetType);
        void registerPacket(PacketType::Server packetType, PacketDecoder decoder);
    };

    namespace Client
    {
        PacketDecoder getPacketDecoder(int packetType);
        void registerPacket(PacketType::Client packetType, PacketDecoder decoder);
    };
}

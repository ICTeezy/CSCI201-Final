#include "packet/PacketRegistry.hpp"

#include <unordered_map>

static std::unordered_map<PacketType::Server, PacketDecoder> serverPacketRegistry;

namespace CatNet::Registry
{
    void Server::registerPacket(PacketType::Server packetType, PacketDecoder decoder)
    {
        serverPacketRegistry[packetType] = decoder;
    }

    PacketDecoder Server::getPacketDecoder(int packetType)
    {
        return serverPacketRegistry[(PacketType::Server) packetType];
    }
};

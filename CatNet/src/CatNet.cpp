#include "CatNet.hpp"

namespace CatNet
{
    void init()
    {
        CatNet::Registry::Server::registerPacket(PacketType::Server::USERNAME, SBUsernamePacket::decode);
    }
}

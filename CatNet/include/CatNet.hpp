#pragma once

#include "buffer/Buffer.hpp"
#include "buffer/BufferView.hpp"
#include "packet/PacketBuilder.hpp"
#include "packet/PacketRegistry.hpp"
#include "packet/PacketType.hpp"

#include "packet/packets/server/SBUsernamePacket.hpp"

namespace CatNet
{
    void init();
}
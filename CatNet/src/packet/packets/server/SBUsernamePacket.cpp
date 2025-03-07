#include "packet/packets/server/SBUsernamePacket.hpp"

#include "packet/PacketType.hpp"

SBUsernamePacket::SBUsernamePacket(std::string username) 
    : m_username(username)
{
    
}

std::string SBUsernamePacket::username() 
{
    return m_username;
}

void* SBUsernamePacket::decode(Buffer& buffer) 
{
    BufferView view = buffer.view();
    std::string username = view.readString();

    SBUsernamePacket* packet = new SBUsernamePacket(username);
    return (void*) packet;
}

Buffer SBUsernamePacket::encode(SBUsernamePacket packet)
{
    Buffer buffer = Buffer::allocatePrefixed(sizeof(unsigned int) + packet.username().length(), (int) PacketType::Server::USERNAME);
    buffer << packet.username();
    return buffer;
}

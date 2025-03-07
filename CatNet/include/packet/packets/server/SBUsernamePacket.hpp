#pragma once

#include <string>

#include "buffer/Buffer.hpp"

class SBUsernamePacket
{

    public:

    SBUsernamePacket(std::string username);
    std::string username();

    static void* decode(Buffer& buffer);
    static Buffer encode(SBUsernamePacket packet);

    private:
    std::string m_username;
};
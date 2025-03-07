project(CatNet)
add_library(${PROJECT_NAME} STATIC
    src/buffer/Buffer.cpp
    src/buffer/BufferView.cpp

    src/packet/PacketBuilder.cpp
    src/packet/PacketRegistry.cpp
    src/CatNet.cpp

    src/packet/packets/server/SBUsernamePacket.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_PROJECT_DIR}include)
project(SocketLib)
add_library(${PROJECT_NAME} src/TCPSocket.cpp src/IPEndpoint.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_PROJECT_DIR}include)
cmake_minimum_required(VERSION 3.3)

project(TcpServerSimulator)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)


set(LIB_SRC TcpServer.h TcpServer.cpp tcpSimulator.cpp)
add_executable(TcpServerSimulator ${LIB_SRC})
TARGET_LINK_LIBRARIES( TcpServerSimulator pthread)

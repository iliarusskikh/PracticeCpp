cmake_minimum_required(VERSION 3.10)
project(SimpleTcp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Server executable
add_executable(server src/server.cpp)

# Client executable
add_executable(client src/client.cpp)

# Include directory for future shared headers (market data, protocol, etc.)
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

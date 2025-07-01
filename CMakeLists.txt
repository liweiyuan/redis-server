cmake_minimum_required(VERSION 3.30)
project(redis-server)

set(CMAKE_CXX_STANDARD 17)

add_executable(redis-server main.cpp
        src/command/command.h src/command/command.cpp
        src/network/network.h src/network/network.cpp
        src/storage/storage.h src/storage/storage.cpp)

target_include_directories(redis-server PUBLIC src)

find_package(Threads REQUIRED)
target_link_libraries(redis-server PRIVATE Threads::Threads)

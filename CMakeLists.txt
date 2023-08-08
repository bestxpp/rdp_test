cmake_minimum_required(VERSION 3.20)
project(simple_client)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

aux_source_directory(./src SRC)

include_directories(3thpart/spdlog/include)
include_directories(3thpart/json/include)

include_directories(/usr/local/include/winpr2)
include_directories(/usr/local/include/freerdp2)

add_executable(simple_client ${SRC})

target_link_libraries(simple_client -pthread -lfreerdp2 -lfreerdp-client2 -lwinpr2)

cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -Wall -pthread")

set(PROJECT_NAME "chat")
project(${PROJECT_NAME})

include_directories(include)
file(GLOB project_SRCS "src/*.cpp")

add_executable(${PROJECT_NAME} ${project_SRCS})

cmake_minimum_required(VERSION 3.5.0)
project(Publisher VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenSSL REQUIRED)

link_libraries(OpenSSL::SSL)
include_directories(/)

add_library(Publisher Publisher.cpp)
add_library(Session Session.cpp)
add_executable(cli_publisher main.cpp)
target_link_libraries(cli_publisher PRIVATE Publisher Session)

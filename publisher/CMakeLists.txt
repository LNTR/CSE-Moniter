cmake_minimum_required(VERSION 3.5.0)
project(Publisher VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenSSL REQUIRED)

link_libraries(wsock32 ws2_32 ${Boost_LIBRARIES} OpenSSL::SSL Boost::json Boost::url)

add_subdirectory(middleware)
# add_executable(cli_publisher publisher/main.cpp)
# target_link_libraries(cli_publisher PRIVATE Publisher Session)
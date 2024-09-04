cmake_minimum_required(VERSION 3.5.0)
project(middleware VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost REQUIRED COMPONENTS json url)
find_package(OpenSSL REQUIRED)
find_package(jwt-cpp CONFIG REQUIRED)


link_libraries(wsock32 ws2_32 ${Boost_LIBRARIES} OpenSSL::SSL Boost::json Boost::url)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(Publisher publisher/Publisher.cpp)
add_library(Server middleware/Server.cpp  middleware/patterns/ObserverPattern.cpp middleware/NotificationQueue.cpp)
add_library(Session publisher/Session.cpp)


add_library(MySqlModel middleware/utils/MySqlModel.cpp)


add_executable(cli_publisher publisher/main.cpp)
target_link_libraries(cli_publisher PRIVATE Publisher Session)
# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/publisher/cert.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


add_executable(middleware_sever middleware/middleware_sever.cpp)
target_link_libraries(middleware_sever PRIVATE Server Session)


add_executable(main main.cpp)
target_link_libraries(main PRIVATE MySqlModel)

# For later use: used for printing variable names in cmake
# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()




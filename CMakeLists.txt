cmake_minimum_required(VERSION 3.5.0)
project(middleware VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost REQUIRED COMPONENTS json url)
find_package(OpenSSL REQUIRED)

link_libraries(wsock32 ws2_32 ${Boost_LIBRARIES} OpenSSL::SSL Boost::json Boost::url)

add_library(Client publisher/Client.cpp)
add_library(Server middleware/Server.cpp  middleware/patterns/ObserverPattern.cpp middleware/NotificationQueue.cpp)
add_library(Session publisher/Session.cpp)

add_library(MySqlModel middleware/utils/MySqlModel.cpp)
target_link_libraries(MySqlModel PRIVATE charconv)
target_include_directories(MySqlModel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})



add_executable(publisher publisher/publisher.cpp)
target_link_libraries(publisher PRIVATE Client Session)
target_include_directories(publisher PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


add_executable(middleware_sever middleware/middleware_sever.cpp)
target_link_libraries(middleware_sever PRIVATE Server Session)
target_include_directories(publisher PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/cert.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR})



# For later use: used for printing variable names in cmake
# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()




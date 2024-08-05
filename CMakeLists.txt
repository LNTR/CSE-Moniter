cmake_minimum_required(VERSION 3.5.0)
project(middleware VERSION 0.1.0 LANGUAGES C CXX)

find_package(Boost REQUIRED COMPONENTS json url)
find_package(OpenSSL REQUIRED)

link_libraries(wsock32 ws2_32 ${Boost_LIBRARIES} OpenSSL::SSL Boost::json Boost::url)

add_library(Client client/Client.cpp)
add_library(Server server/Server.cpp server/ObserverPattern.cpp server/NotificationQueue.cpp)
add_library(Session utils/Session.cpp)


add_executable(subscriber subscriber.cpp)
target_link_libraries(subscriber PRIVATE Client)

add_executable(publisher publisher.cpp)
target_link_libraries(publisher PRIVATE Client)


add_executable(middleware_sever middleware_sever.cpp)
target_link_libraries(middleware_sever PRIVATE Server)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/cert.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR})



# For later use: used for printing variable names in cmake
# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()




cmake_minimum_required(VERSION 3.5.0)
project(middleware VERSION 0.1.0 LANGUAGES C CXX)

find_package(Boost COMPONENTS REQUIRED)
link_libraries(wsock32 ws2_32 ${Boost_LIBRARIES})

add_library(Client client/Client.cpp)
add_library(Server server/Server.cpp server/ObserverPattern.cpp server/NotificationQueue.cpp)

add_executable(subscriber subscriber.cpp)
target_link_libraries(subscriber PRIVATE Client)

add_executable(publisher publisher.cpp)
target_link_libraries(publisher PRIVATE Client)


add_executable(middleware_sever middleware_sever.cpp)
target_link_libraries(middleware_sever PRIVATE Server)


add_executable(test test2.cpp)



# For later use: used for printing variable names in cmake
# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()




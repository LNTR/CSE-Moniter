cmake_minimum_required(VERSION 3.5.0)
project(Middleware VERSION 0.1.0 LANGUAGES C CXX)

find_package(jwt-cpp CONFIG REQUIRED)

include_directories(/)


add_library(Client users/Client.cpp patterns/ObserverPattern.cpp NotificationQueue.cpp)
add_library(MySqlModel utils/MySqlModel.cpp)


add_executable(middleware_sever middleware_sever.cpp users/ContentPublisher.cpp users/WebSubscriber.cpp)
target_link_libraries(middleware_sever PRIVATE Client)


cmake_minimum_required(VERSION 3.5.0)
project(CSE-Moniter VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost REQUIRED COMPONENTS json url)

link_libraries(wsock32 ws2_32 ${Boost_LIBRARIES}  Boost::json Boost::url)
add_subdirectory(middleware)
add_subdirectory(publisher)

# file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/publisher/cert.pem DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# add_executable(main main.cpp)
# target_link_libraries(main PRIVATE MySqlModel)

# For later use: used for printing variable names in cmake
# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()



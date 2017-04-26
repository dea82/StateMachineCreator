cmake_minimum_required(VERSION 3.2.2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

# Enable CCache if found
include(${CMAKE_SOURCE_DIR}/cmake/CCache.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/iwyu.cmake)
iwyu_check(ON)

project(StateMachineCreator CXX)

add_subdirectory(creator)
add_subdirectory(server)

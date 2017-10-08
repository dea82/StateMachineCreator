# CMake root
cmake_minimum_required(VERSION 3.2.2)

# CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/src/cmake/Modules/")

# Compiler settings
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -Wpedantic")

# Enable CCache if found
include(${CMAKE_SOURCE_DIR}/src/cmake/CCache.cmake)
# Include What You Use
include(${CMAKE_SOURCE_DIR}/src/cmake/iwyu.cmake)
iwyu_check(OFF)

# Qt stuff
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

project(StateMachineCreator CXX)

add_subdirectory(src)
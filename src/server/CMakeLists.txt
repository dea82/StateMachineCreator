#find_package(ZeroMQ REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR)
set(SRC_FILES main.cpp)
add_executable(server ${SRC_FILES})
target_include_directories(server PUBLIC ${CONAN_INCLUDE_DIRS})
target_link_libraries(server CONAN_PKG::cppzmq )
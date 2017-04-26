find_package(ZeroMQ REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR)
set(SRC_FILES main.cpp)
add_executable(server ${SRC_FILES})
target_include_directories(server PUBLIC ${ZeroMQ_INCLUDE_DIR})
target_link_libraries(server ${ZeroMQ_LIBRARY})
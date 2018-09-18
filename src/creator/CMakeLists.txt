set(TARGET_NAME creator)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(${TARGET_NAME} ${SRC_FILES})
target_link_libraries(${TARGET_NAME} gui)
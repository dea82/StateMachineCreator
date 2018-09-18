set(TARGET_NAME server)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${TARGET_NAME} ${SRC_FILES})
target_include_directories(${TARGET_NAME} PUBLIC include)
target_link_libraries(${TARGET_NAME} PRIVATE CONAN_PKG::cppzmq)
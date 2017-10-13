# Requires environment variable CMAKE_PREFIX_PATH
# set to Qt lib, ~/Qt/5.7/gcc_64)
find_package(Qt5Core REQUIRED)
find_package(Qt5Svg REQUIRED)
#message(STATUS "Qt version: ${Qt5Widgets_VERSION}")
#find_package(ZeroMQ REQUIRED)

file(GLOB SRC_FILES *.qrc *.cpp)
add_executable(creator ${SRC_FILES})
#target_include_directories(creator PUBLIC ${CONAN_INCLUDE_DIRS})
target_link_libraries(creator Qt5::Core Qt5::Svg)

add_subdirectory(test)
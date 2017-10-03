# Requires environment variable CMAKE_PREFIX_PATH
# set to Qt lib, ~/Qt/5.7/gcc_64
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Svg REQUIRED)
message(STATUS "Qt version: ${Qt5Widgets_VERSION}")
find_package(ZeroMQ REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR)
file(GLOB SRC_FILES *.qrc *.cpp)
add_executable(creator ${SRC_FILES})
target_include_directories(creator PUBLIC ${ZeroMQ_INCLUDE_DIR})
target_link_libraries(creator Qt5::Widgets Qt5::Svg ${ZeroMQ_LIBRARY})
# Requires environment variable CMAKE_PREFIX_PATH
# set to Qt lib, ~/Qt/5.7/gcc_64
find_package(Qt5Widgets REQUIRED)
message(STATUS "Qt version: ${Qt5Widgets_VERSION}")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR)
set(SRC_FILES graphics.qrc main.cpp MainWindow.cpp WorkAreaView.cpp WorkAreaScene.cpp State.cpp InsertElementToolBar.cpp)
add_executable(creator ${SRC_FILES})
target_link_libraries(creator Qt5::Widgets)

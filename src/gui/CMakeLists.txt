set(TARGET_NAME gui)

# Still necessary as conan does not generate Qt target correctly
find_package(Qt5Core REQUIRED)
find_package(Qt5Svg REQUIRED)

# Qt stuff
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Generated moc code
set(CMAKE_INCLUDE_CURRENT_DIR ON)


file(GLOB_RECURSE SRC_FILES src/*.cpp resources/*.qrc)
add_library(${TARGET_NAME} ${SRC_FILES})
target_link_libraries(${TARGET_NAME} Qt5::Core Qt5::Svg)
target_include_directories(${TARGET_NAME}  PUBLIC include)
target_include_directories(${TARGET_NAME} PUBLIC src)

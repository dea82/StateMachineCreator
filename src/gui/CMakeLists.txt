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


file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.hpp src/*.cc src/*.h resources/*.qrc)
file(GLOB_RECURSE UI_FILES src/*.ui)

add_library(${TARGET_NAME} ${SRC_FILES} ${UI_FILES})

# Fix to get code completion in IDE for generated ui files
set_target_properties(${TARGET_NAME} PROPERTIES AUTOGEN_BUILD_DIR "${CMAKE_SOURCE_DIR}/generated")

target_link_libraries(${TARGET_NAME} model Qt5::Core Qt5::Svg)
target_include_directories(${TARGET_NAME}  PUBLIC include)
target_include_directories(${TARGET_NAME} PRIVATE src ${CMAKE_SOURCE_DIR}/generated/include)

include(GoogleTest)
find_package(Qt5Core REQUIRED)
find_package(Qt5Test REQUIRED)

# Internal API test
file(GLOB_RECURSE TEST_INTERNAL_SRC test/internal/*.cc)
add_executable(${TARGET_NAME}_internal_test ${TEST_INTERNAL_SRC})
gtest_discover_tests(${TARGET_NAME}_internal_test)
target_link_libraries(${TARGET_NAME}_internal_test ${TARGET_NAME} CONAN_PKG::gtest test-helpers Qt5::Core Qt5::Test)
target_include_directories(${TARGET_NAME}_internal_test PRIVATE src test)

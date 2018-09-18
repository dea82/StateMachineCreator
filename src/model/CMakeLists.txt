include(GoogleTest)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB_RECURSE SRC_FILES "src/model/*.cpp")

add_library(model ${SRC_FILES})
target_link_libraries(model CONAN_PKG::tinyxml)
target_include_directories(model PUBLIC include)
target_include_directories(model PRIVATE src)

find_package(GTest REQUIRED)
find_package(GMock REQUIRED)
find_package(Threads REQUIRED)

file(GLOB_RECURSE TEST_SRC "test/*.cpp")
add_executable(model_test ${TEST_SRC})
gtest_discover_tests(model_test)
target_link_libraries(model_test model GTest::GTest GTest::Main GMock::GMock Threads::Threads)
target_include_directories(model_test PUBLIC test/include ${GTEST_INCLUDE_DIR})
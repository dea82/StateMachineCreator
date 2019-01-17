include(GoogleTest)

file(GLOB_RECURSE SRC_FILES "src/model/*.cpp" "src/model/*.cc")

add_library(model ${SRC_FILES})
target_link_libraries(model common CONAN_PKG::tinyxml)
target_include_directories(model PUBLIC include)
target_include_directories(model PRIVATE src)

file(GLOB_RECURSE TEST_SRC "test/*.cpp")
add_executable(model_test ${TEST_SRC})
gtest_discover_tests(model_test)
target_link_libraries(model_test model CONAN_PKG::gtest)
target_include_directories(model_test PUBLIC test/include)


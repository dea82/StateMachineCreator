find_package(Qt5Test REQUIRED)

add_executable(foo testqstring.cpp)
add_test(Olle foo)

target_link_libraries(foo Qt5::Test)
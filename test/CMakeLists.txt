cmake_minimum_required(VERSION 3.10)

include(GoogleTest)

add_executable(test_keyword
    contains.cpp
    example.cpp
    unique.cpp
)
target_link_libraries(test_keyword keyword ${CONAN_LIBS})

gtest_discover_tests(test_keyword)

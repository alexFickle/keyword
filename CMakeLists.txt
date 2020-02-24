cmake_minimum_required(VERSION 3.10)

project(keyword CXX)

include(CTest)

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(keyword INTERFACE)
target_include_directories(keyword INTERFACE include)
target_compile_features(keyword INTERFACE cxx_std_17)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()

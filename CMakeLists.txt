cmake_minimum_required(VERSION 3.16)

project(FossilTest
    VERSION 2.0.6
    LANGUAGES C CXX
    DESCRIPTION "Fossil Test unit testing framework"
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(FOSSIL_TEST_WITH_TESTS "Build and register Fossil Test self-tests" OFF)
option(FOSSIL_TEST_BUILD_SHARED "Build fossil_test as a shared library" OFF)

if(APPLE)
    enable_language(OBJC)
    enable_language(OBJCXX)
endif()

add_subdirectory(code)

include(CTest)
if(FOSSIL_TEST_WITH_TESTS AND BUILD_TESTING)
    add_subdirectory(code/tests)
endif()
# code/tests/CMakeLists.txt

option(WITH_TEST "Enable unit tests" OFF)

if(WITH_TEST)
    find_package(Python3 REQUIRED)

    # Run the Python script to generate the runner
    execute_process(
        COMMAND Python3_EXECUTABLE ${CMAKE_SOURCE_DIR}/tools/generate-runner.py
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        RESULT_VARIABLE GENERATE_RUNNER_RESULT
    )

    if(NOT GENERATE_RUNNER_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to generate unit runner")
    endif()

    set(TEST_C ${CMAKE_SOURCE_DIR}/unit_runner.c)

    set(TEST_CASES sample bdd tdd ddd mark mock)

    foreach(CASE ${TEST_CASES})
        list(APPEND TEST_C ${CMAKE_SOURCE_DIR}/cases/test_${CASE}.c)
        list(APPEND TEST_C ${CMAKE_SOURCE_DIR}/cases/test_${CASE}.cpp)
    endforeach()

    add_executable(testbed-c ${TEST_C})

    target_include_directories(testbed-c PRIVATE ${PROJECT_SOURCE_DIR}/include)
    target_link_libraries(testbed-c PRIVATE fossil_test_dep)

    add_test(NAME "fossil_testing_C" COMMAND testbed-c)
endif()

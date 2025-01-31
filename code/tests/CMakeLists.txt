# code/tests/CMakeLists.txt

option(WITH_TEST "Enable testing" OFF)

if(WITH_TEST)
    # Run the Python script to generate the runner
    execute_process(
        COMMAND ${CMAKE_SOURCE_DIR}/tools/generate-runner.py
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        RESULT_VARIABLE RUNNER_GEN_RESULT
    )
    if(NOT RUNNER_GEN_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to generate test runner")
    endif()

    set(TEST_C "unit_runner.c")
    set(TEST_CASES sample bdd tdd ddd mark mock)

    foreach(CASE ${TEST_CASES})
        list(APPEND TEST_C "cases/test_${CASE}.c")
        list(APPEND TEST_C "cases/test_${CASE}.cpp")
    endforeach()

    add_executable(testbed-c ${TEST_C})
    target_include_directories(testbed-c PRIVATE ${CMAKE_SOURCE_DIR}/include)
    target_link_libraries(testbed-c PRIVATE fossil_test_dep)

    add_test(NAME "fossil_testing_C" COMMAND testbed-c)
endif()

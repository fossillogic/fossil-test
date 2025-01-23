# logic/tests/CMakeLists.txt

# Check if testing is enabled
option(WITH_TEST "Enable building and running tests" ON)

if(WITH_TEST)
    # Run the generate-runner.py script
    execute_process(
        COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/../tools/generate-runner.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE GENERATE_RUNNER_RESULT
    )
    if(NOT GENERATE_RUNNER_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to run generate-runner.py")
    endif()

    # Define the test sources
    set(TEST_C ${CMAKE_CURRENT_SOURCE_DIR}/unit_runner.c)

    # Define test cases
    set(TEST_CASES sample bdd tdd ddd mark mock)

    # Append the test case sources
    foreach(CASE IN LISTS TEST_CASES)
        list(APPEND TEST_C
            ${CMAKE_CURRENT_SOURCE_DIR}/cases/test_${CASE}.c
            ${CMAKE_CURRENT_SOURCE_DIR}/cases/test_${CASE}.cpp
        )
    endforeach()

    # Create the executable for tests
    add_executable(testbed-c ${TEST_C})

    # Link dependencies and include directories
    target_include_directories(testbed-c PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
    target_link_libraries(testbed-c PRIVATE fossil_test_dep)

    # Add the test
    enable_testing()
    add_test(NAME "fossil testing C" COMMAND testbed-c)
endif()

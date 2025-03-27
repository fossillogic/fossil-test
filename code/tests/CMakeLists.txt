if (WITH_TEST)
    execute_process(
        COMMAND python3 ${CMAKE_SOURCE_DIR}/tools/generate-runner.py
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE RUNNER_GENERATION_RESULT
    )
    if(NOT RUNNER_GENERATION_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to generate runner")
    endif()

    set(TEST_C unit_runner.c)
    set(TEST_CASES sample bdd tdd ddd mark mock)

    foreach(CASE IN LISTS TEST_CASES)
        list(APPEND TEST_C cases/test_${CASE}.c)
        list(APPEND TEST_C cases/test_${CASE}.cpp)
    endforeach()

    add_executable(testbed-c ${TEST_C})
    target_include_directories(testbed-c PRIVATE ${DIR})
    target_link_libraries(testbed-c PRIVATE fossil_test_dep)

    add_test(NAME "fossil testing C" COMMAND testbed-c)
endif()
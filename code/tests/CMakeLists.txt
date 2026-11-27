find_package(Python3 COMPONENTS Interpreter REQUIRED)

set(FOSSIL_TEST_CASES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cases")
set(FOSSIL_TEST_UNIT_RUNNER "${CMAKE_CURRENT_BINARY_DIR}/unit_runner.c")

file(GLOB FOSSIL_TEST_CASE_SOURCES
    CONFIGURE_DEPENDS
    "${FOSSIL_TEST_CASES_DIR}/test_*.c"
    "${FOSSIL_TEST_CASES_DIR}/test_*.cpp"
)

if(APPLE)
    file(GLOB FOSSIL_TEST_OBJC_SOURCES
        CONFIGURE_DEPENDS
        "${FOSSIL_TEST_CASES_DIR}/test_*.m"
        "${FOSSIL_TEST_CASES_DIR}/test_*.mm"
    )
    list(APPEND FOSSIL_TEST_CASE_SOURCES ${FOSSIL_TEST_OBJC_SOURCES})
endif()

# runner.py writes unit_runner.c into its cwd (code/tests/)
add_custom_command(
    OUTPUT "${FOSSIL_TEST_UNIT_RUNNER}"
    COMMAND ${CMAKE_COMMAND} -E chdir "${CMAKE_CURRENT_SOURCE_DIR}"
            ${Python3_EXECUTABLE} tools/runner.py
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/unit_runner.c"
            "${FOSSIL_TEST_UNIT_RUNNER}"
    DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/tools/runner.py"
        ${FOSSIL_TEST_CASE_SOURCES}
    COMMENT "Generating Fossil Test unit_runner.c via Python"
    VERBATIM
)

add_executable(maip
    ${FOSSIL_TEST_UNIT_RUNNER}
    ${FOSSIL_TEST_CASE_SOURCES}
)

target_include_directories(maip PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../logic
)

target_link_libraries(maip PRIVATE fossil_test)

add_test(NAME fossil_testing_C COMMAND maip)
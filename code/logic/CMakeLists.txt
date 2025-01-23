# code/logic/CMakeLists.txt

# Define the include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# List the source files
set(TEST_CODE
    mocking.c
    testing.c
    marking.c
)

# Create the library target
add_library(fossil-test STATIC ${TEST_CODE})

# Set the library to be installed
install(TARGETS fossil-test
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Declare the dependency
add_library(fossil_test_dep INTERFACE)
target_link_libraries(fossil_test_dep INTERFACE fossil-test)
target_include_directories(fossil_test_dep INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

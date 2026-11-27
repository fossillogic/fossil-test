set(FOSSIL_TEST_SOURCES
    mock.c
    test.c
    mark.c
    mutate.c
    sanity.c
    common.c
)

if(FOSSIL_TEST_BUILD_SHARED)
    add_library(fossil_test SHARED ${FOSSIL_TEST_SOURCES})
else()
    add_library(fossil_test STATIC ${FOSSIL_TEST_SOURCES})
endif()

add_library(FossilTest::fossil_test ALIAS fossil_test)

target_include_directories(fossil_test
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

if(UNIX)
    target_compile_definitions(fossil_test PRIVATE _POSIX_C_SOURCE=200112L)
endif()

find_library(FOSSIL_TEST_LIBM m)
if(FOSSIL_TEST_LIBM)
    target_link_libraries(fossil_test PUBLIC ${FOSSIL_TEST_LIBM})
endif()

if(WIN32)
    target_link_libraries(fossil_test PUBLIC kernel32)
endif()

set_target_properties(fossil_test PROPERTIES
    OUTPUT_NAME fossil_test
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    EXPORT_NAME fossil_test
)

install(TARGETS fossil_test
    EXPORT FossilTestTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY fossil/
    DESTINATION include/fossil
    FILES_MATCHING
        PATTERN "*.h"
)

install(EXPORT FossilTestTargets
    FILE FossilTestTargets.cmake
    NAMESPACE FossilTest::
    DESTINATION lib/cmake/FossilTest
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/FossilTestConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/FossilTestConfig.cmake"
"include(\"\${CMAKE_CURRENT_LIST_DIR}/FossilTestTargets.cmake\")\n")

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/FossilTestConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/FossilTestConfigVersion.cmake"
    DESTINATION lib/cmake/FossilTest
)
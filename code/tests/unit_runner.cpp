
// Generated Fossil Logic Test
#include <fossil/test/framework.h>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test List
// * * * * * * * * * * * * * * * * * * * * * * * *
FOSSIL_TEST_EXPORT(cpp_bdd_test_cases);
FOSSIL_TEST_EXPORT(cpp_sample_test_cases);
FOSSIL_TEST_EXPORT(cpp_tdd_test_cases);
FOSSIL_TEST_EXPORT(c_tdd_test_cases);
FOSSIL_TEST_EXPORT(c_sample_test_cases);
FOSSIL_TEST_EXPORT(c_bdd_test_cases);
// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Runner
// * * * * * * * * * * * * * * * * * * * * * * * *
int main(int argc, char **argv) {
    FOSSIL_TEST_START(argc, argv);
    FOSSIL_TEST_IMPORT(cpp_bdd_test_cases);
    FOSSIL_TEST_IMPORT(cpp_sample_test_cases);
    FOSSIL_TEST_IMPORT(cpp_tdd_test_cases);
    FOSSIL_TEST_IMPORT(c_tdd_test_cases);
    FOSSIL_TEST_IMPORT(c_sample_test_cases);
    FOSSIL_TEST_IMPORT(c_bdd_test_cases);
    FOSSIL_TEST_RUN();
    FOSSIL_TEST_SUMMARY();
    FOSSIL_TEST_END();
} // end of func

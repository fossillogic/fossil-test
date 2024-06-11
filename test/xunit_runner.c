
// Generated Fossil Logic Test

#include <fossil/unittest.h>


// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test List
// * * * * * * * * * * * * * * * * * * * * * * * *

FOSSIL_TEST_EXPORT(fossil_mockup_spy_group);
FOSSIL_TEST_EXPORT(tags_test_group);
FOSSIL_TEST_EXPORT(fossil_mockup_input_group);
FOSSIL_TEST_EXPORT(fossil_mockup_network_group);
FOSSIL_TEST_EXPORT(fossil_mockup_output_group);
FOSSIL_TEST_EXPORT(fossil_mockup_stub_group);
FOSSIL_TEST_EXPORT(benchmark_group);
FOSSIL_TEST_EXPORT(fossil_mockup_inject_group);
FOSSIL_TEST_EXPORT(markers_test_group);
FOSSIL_TEST_EXPORT(fixture_test_group);
FOSSIL_TEST_EXPORT(fossil_mockup_file_group);
FOSSIL_TEST_EXPORT(bdd_test_group);
FOSSIL_TEST_EXPORT(tdd_test_group);
FOSSIL_TEST_EXPORT(fossil_mockup_behav_group);
FOSSIL_TEST_EXPORT(fossil_mockup_fake_group);
FOSSIL_TEST_EXPORT(fossil_mockup_group);

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Runner
// * * * * * * * * * * * * * * * * * * * * * * * *
int main(int argc, char **argv) {
    FOSSIL_TEST_CREATE(argc, argv);
    FOSSIL_TEST_IMPORT(fossil_mockup_spy_group);
    FOSSIL_TEST_IMPORT(tags_test_group);
    FOSSIL_TEST_IMPORT(fossil_mockup_input_group);
    FOSSIL_TEST_IMPORT(fossil_mockup_network_group);
    FOSSIL_TEST_IMPORT(fossil_mockup_output_group);
    FOSSIL_TEST_IMPORT(fossil_mockup_stub_group);
    FOSSIL_TEST_IMPORT(benchmark_group);
    FOSSIL_TEST_IMPORT(fossil_mockup_inject_group);
    FOSSIL_TEST_IMPORT(markers_test_group);
    FOSSIL_TEST_IMPORT(fixture_test_group);
    FOSSIL_TEST_IMPORT(fossil_mockup_file_group);
    FOSSIL_TEST_IMPORT(bdd_test_group);
    FOSSIL_TEST_IMPORT(tdd_test_group);
    FOSSIL_TEST_IMPORT(fossil_mockup_behav_group);
    //FOSSIL_TEST_IMPORT(fossil_mockup_fake_group);
    //FOSSIL_TEST_IMPORT(fossil_mockup_group);

    FOSSIL_TEST_RUN();
    return FOSSIL_TEST_ERASE();
} // end of func

import os
import re


class TestRunnerGenerator:
    def __init__(self):
        # Set the directory to a subdirectory named 'cases' within the current working directory
        self.directory = os.path.join(os.getcwd(), "cases")

    def find_test_groups(self):
        test_groups = set()
        pattern = r"FOSSIL_TEST_GROUP\((\w+)\)"

        # Walk through files in the specified directory, 'cases'
        for root, _, files in os.walk(self.directory):
            for file in files:
                # Search for files that start with "test_" and end with either ".c" or ".cpp"
                if file.startswith("test_") and (file.endswith(".c") or file.endswith(".cpp")):
                    with open(os.path.join(root, file), "r") as f:
                        content = f.read()
                        matches = re.findall(pattern, content)
                        test_groups.update(matches)

        return list(test_groups)

    def generate_test_runner(self, test_groups):
        # Prepare header content
        header = """
// Generated Fossil Logic Test
#include <fossil/test/framework.h>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test List
// * * * * * * * * * * * * * * * * * * * * * * * *
"""

        # Declare test group externs
        extern_pools = "\n".join(
            [f"FOSSIL_TEST_EXPORT({group});" for group in test_groups]
        )

        # Prepare runner content
        runner = """
// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Runner
// * * * * * * * * * * * * * * * * * * * * * * * *
int main(int argc, char **argv) {
    FOSSIL_TEST_START(argc, argv);\n"""

        # Import test groups in the main function
        import_pools = "\n".join(
            [f"    FOSSIL_TEST_IMPORT({group});" for group in test_groups]
        )

        # Complete with footer
        footer = """
    FOSSIL_TEST_RUN();
    FOSSIL_TEST_SUMMARY();
    FOSSIL_TEST_END();
} // end of func
"""

        # Write the generated content to 'unit_runner.c'
        with open("unit_runner.cpp", "w") as file:
            file.write(header)
            file.write(extern_pools)
            file.write(runner)
            file.write(import_pools)
            file.write(footer)


# Instantiate the generator, find test groups, and generate the test runner
generator = TestRunnerGenerator()
test_groups = generator.find_test_groups()
generator.generate_test_runner(test_groups)

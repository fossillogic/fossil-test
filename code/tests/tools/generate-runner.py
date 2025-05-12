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
                # Search for C and C++ files
                if (file.startswith("test_") and file.endswith(".c")) or file.endswith(".cpp"):
                    with open(os.path.join(root, file), "r") as f:
                        content = f.read()
                        matches = re.findall(pattern, content)
                        test_groups.update(matches)

        return list(test_groups)

    def generate_c_runner(self, test_groups):
        # Prepare header content for the test runner
        header = """
// Generated Fossil Logic Test Runner
#include <fossil/pizza/framework.h>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test List
// * * * * * * * * * * * * * * * * * * * * * * * *
"""

        # Declare test group externs
        extern_test_groups = "\n".join(
            [f"FOSSIL_TEST_EXPORT({group});" for group in test_groups]
        )

        # Prepare runner content
        runner = """\n
// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Runner
// * * * * * * * * * * * * * * * * * * * * * * * *
int main(int argc, char **argv) {
    FOSSIL_TEST_START(argc, argv);\n"""

        # Import test groups in the main function
        import_test_groups = "\n".join(
            [f"    FOSSIL_TEST_IMPORT({group});" for group in test_groups]
        )

        # Complete with footer
        footer = """\n
    FOSSIL_RUN_ALL();
    FOSSIL_SUMMARY();
    return FOSSIL_END();
} // end of main
"""

        # Write the generated test runner to 'unit_runner.c'
        with open("unit_runner.c", "w") as file:
            file.write(header)
            file.write(extern_test_groups)
            file.write(runner)
            file.write(import_test_groups)
            file.write(footer)


# Instantiate the generator, find test groups, and generate the test runner
generator = TestRunnerGenerator()
test_groups = generator.find_test_groups()

# Generate the test runner for C and C++ tests
generator.generate_c_runner(test_groups)

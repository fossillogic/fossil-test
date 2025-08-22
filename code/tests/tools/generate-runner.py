import os
import re
import sys


class TestRunnerGenerator:
    def __init__(self):
        # Set the directory to a subdirectory named 'cases' within the current working directory
        self.directory = os.path.join(os.getcwd(), "cases")
        # Detect if running on Apple (macOS)
        self.is_apple = sys.platform == "darwin"

    def find_test_groups(self):
        c_cpp_groups = set()
        objc_groups = set()
        objcpp_groups = set()
        pattern = r"FOSSIL_TEST_GROUP\((\w+)\)"

        # Walk through files in the specified directory, 'cases'
        for root, _, files in os.walk(self.directory):
            for file in files:
                if file.startswith("test_"):
                    file_path = os.path.join(root, file)
                    with open(file_path, "r") as f:
                        content = f.read()
                        matches = re.findall(pattern, content)
                        if file.endswith(".c") or file.endswith(".cpp"):
                            c_cpp_groups.update(matches)
                        elif self.is_apple and file.endswith(".m"):
                            objc_groups.update(matches)
                        elif self.is_apple and file.endswith(".mm"):
                            objcpp_groups.update(matches)

        return list(c_cpp_groups), list(objc_groups), list(objcpp_groups)

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
c_cpp_groups, objc_groups, objcpp_groups = generator.find_test_groups()

# Only include Objective-C/Objective-C++ groups if on Apple
test_groups = c_cpp_groups
if generator.is_apple:
    test_groups += objc_groups + objcpp_groups

# Generate the test runner for C and C++ (and Objective-C/Objective-C++ on Apple) tests
generator.generate_c_runner(test_groups)

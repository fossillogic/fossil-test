import os
import re


class TestRunnerGenerator:
    def __init__(self):
        # Set the directory to a subdirectory named 'cases' within the current working directory
        self.directory = os.path.join(os.getcwd(), "cases")

    def find_test_groups(self):
        c_test_groups = set()
        cpp_test_groups = set()
        pattern = r"FOSSIL_TEST_GROUP\((\w+)\)"

        # Walk through files in the specified directory, 'cases'
        for root, _, files in os.walk(self.directory):
            for file in files:
                # Search for C files
                if file.startswith("test_") and file.endswith(".c"):
                    with open(os.path.join(root, file), "r") as f:
                        content = f.read()
                        matches = re.findall(pattern, content)
                        c_test_groups.update(matches)
                # Search for C++ files
                elif file.startswith("test_") and file.endswith(".cpp"):
                    with open(os.path.join(root, file), "r") as f:
                        content = f.read()
                        matches = re.findall(pattern, content)
                        cpp_test_groups.update(matches)

        return list(c_test_groups), list(cpp_test_groups)

    def generate_c_runner(self, c_test_groups):
        # Prepare header content for C test runner
        header = """
// Generated Fossil Logic Test (C)
#include <fossil/test/framework.h>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test List (C)
// * * * * * * * * * * * * * * * * * * * * * * * *
"""

        # Declare C test group externs within extern "C"
        extern_c_pools = "\n".join(
            [f"FOSSIL_TEST_EXPORT({group});" for group in c_test_groups]
        )

        # Prepare runner content for C
        runner = """\n
// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Runner (C)
// * * * * * * * * * * * * * * * * * * * * * * * *
int main(int argc, char **argv) {
    FOSSIL_TEST_START(argc, argv);\n"""

        # Import C test groups in the main function
        import_c_pools = "\n".join(
            [f"    FOSSIL_TEST_IMPORT({group});" for group in c_test_groups]
        )

        # Complete with footer
        footer = """\n
    FOSSIL_TEST_RUN();
    FOSSIL_TEST_SUMMARY();
    FOSSIL_TEST_END();
} // end of func
"""

        # Write the generated C test runner to 'unit_runner_c.cpp'
        with open("unit_runner.c", "w") as file:
            file.write(header)
            file.write(extern_c_pools)
            file.write(runner)
            file.write(import_c_pools)
            file.write(footer)

    def generate_cpp_runner(self, cpp_test_groups):
        # Prepare header content for C++ test runner
        header = """
// Generated Fossil Logic Test (C++)
#include <fossil/test/framework.h>

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test List (C++)
// * * * * * * * * * * * * * * * * * * * * * * * *
"""

        # Declare C++ test group externs
        extern_cpp_pools = "\n".join(
            [f"FOSSIL_TEST_EXPORT({group});" for group in cpp_test_groups]
        )

        # Prepare runner content for C++
        runner = """\n
// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Runner (C++)
// * * * * * * * * * * * * * * * * * * * * * * * *
int main(int argc, char **argv) {
    FOSSIL_TEST_START(argc, argv);\n"""

        # Import C++ test groups in the main function
        import_cpp_pools = "\n".join(
            [f"    FOSSIL_TEST_IMPORT({group});" for group in cpp_test_groups]
        )

        # Complete with footer
        footer = """\n
    FOSSIL_TEST_RUN();
    FOSSIL_TEST_SUMMARY();
    FOSSIL_TEST_END();
} // end of func
"""

        # Write the generated C++ test runner to 'unit_runner_cpp.cpp'
        with open("unit_runner.cpp", "w") as file:
            file.write(header)
            file.write(extern_cpp_pools)
            file.write(runner)
            file.write(import_cpp_pools)
            file.write(footer)


# Instantiate the generator, find test groups, and generate the test runners
generator = TestRunnerGenerator()
c_test_groups, cpp_test_groups = generator.find_test_groups()

# Generate separate runners for C and C++
generator.generate_c_runner(c_test_groups)
generator.generate_cpp_runner(cpp_test_groups)

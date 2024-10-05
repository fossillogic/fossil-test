import os
import re


class TestRunnerGenerator:
    def __init__(self):
        self.directory = os.getcwd()

    def find_test_groups(self):
        test_groups = set()
        pattern = r"FOSSIL_TEST_GROUP\((\w+)\)"

        for root, _, files in os.walk(self.directory):
            for file in files:
                if file.startswith("test_") and file.endswith(".c"):
                    with open(os.path.join(root, file), "r") as f:
                        content = f.read()
                        matches = re.findall(pattern, content)
                        test_groups.update(matches)

        return list(test_groups)

    def generate_test_runner(self, test_groups):
        header = """
// Generated Fossil Logic Test
"""

        header += """
#include <fossil/unittest/framework.h>
"""

        header += """

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test List
// * * * * * * * * * * * * * * * * * * * * * * * *\n"""

        extern_pools = "\n".join(
            [f"FOSSIL_TEST_EXPORT({group});" for group in test_groups]
        )

        runner = """

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Runner
// * * * * * * * * * * * * * * * * * * * * * * * *"""

        runner += """
int main(int argc, char **argv) {
    FOSSIL_TEST_CREATE(argc, argv);\n"""

        import_pools = "\n".join(
            [f"    FOSSIL_TEST_IMPORT({group});" for group in test_groups]
        )

        footer = """
    FOSSIL_TEST_RUN();
    return FOSSIL_TEST_ERASE();
} // end of func
"""

        with open("unit_runner.c", "w") as file:
            file.write(header)
            file.write("\n")
            file.write(extern_pools)
            file.write(runner)
            file.write(import_pools)
            file.write("\n")
            file.write(footer)


generator = TestRunnerGenerator()
test_groups = generator.find_test_groups()
generator.generate_test_runner(test_groups)

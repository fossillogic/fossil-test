import os
import re

class TestRunnerGenerator:
    def __init__(self):
        self.directory = os.getcwd()

    def find_test_groups(self, extension):
        test_groups = set()
        pattern = r'FOSSIL_TEST_GROUP\((\w+)\)'

        for root, _, files in os.walk(self.directory):
            for file in files:
                if file.startswith('fossil_test_') and file.endswith('.' + extension):
                    with open(os.path.join(root, file), 'r') as f:
                        content = f.read()
                        matches = re.findall(pattern, content)
                        test_groups.update(matches)

        return list(test_groups)

    def generate_test_runner(self, test_groups, extension):
        header = """
// Generated Fossil Logic Test
"""

        if extension == 'c':
            header += """
#include <fossil/unittest.h>
"""
        elif extension == 'cpp':
            header += """
#include <fossil/unittest.h>
"""
        elif extension == 'm':
            header += """
#import <fossil/unittest.h>
"""
        elif extension == 'mm':
            header += """
#import <fossil/unittest.h>
"""

        header += """

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test List
// * * * * * * * * * * * * * * * * * * * * * * * *\n"""

        extern_pools = '\n'.join([f"FOSSIL_TEST_EXTERN_POOL({group});" for group in test_groups])

        runner = """

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Fossil Logic Test Runner
// * * * * * * * * * * * * * * * * * * * * * * * *"""

        if extension == 'c':
            runner += """
int main(int argc, char **argv) {
    FOSSIL_TEST_CREATE(argc, argv);\n"""
        elif extension == 'cpp':
            runner += """
int main(int argc, char **argv) {
    FOSSIL_TEST_CREATE(argc, argv);\n"""
        elif extension == 'm':
            runner += """
int main(int argc, const char **argv) {
    FOSSIL_TEST_CREATE(argc, argv);\n\n"""
        elif extension == 'mm':
            runner += """
int main(int argc, const char **argv) {
    FOSSIL_TEST_CREATE(argc, argv);\n\n"""

        import_pools = '\n'.join([f"    FOSSIL_TEST_IMPORT_POOL({group});" for group in test_groups])

        footer = """
    FOSSIL_TEST_RUN();
    return FOSSIL_TEST_ERASE();
} // end of func
"""

        with open(f'xunit_runner.{extension}', 'w') as file:
            file.write(header)
            file.write("\n")
            file.write(extern_pools)
            file.write(runner)
            file.write(import_pools)
            file.write("\n")
            file.write(footer)

generator = TestRunnerGenerator()
extensions = ['c']
for ext in extensions:
    test_groups = generator.find_test_groups(ext)
    generator.generate_test_runner(test_groups, ext)

test_code = ['commands.c', 'console.c', 'unittest.c']

fossil_test_lib = library('fossil-test',
    test_code,
    install: true,
    include_directories: dir)

fossil_test_dep = declare_dependency(
    link_with: fossil_test_lib,
    include_directories: dir)

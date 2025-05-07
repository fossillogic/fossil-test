dir = include_directories('.')

test_code = ['mock.c', 'test.c', 'mark.c',
            # internal source files below
             'stream.c']

fossil_test_lib = library('fossil-test',
    test_code,
    install: true,
    include_directories: dir)

fossil_test_dep = declare_dependency(
    link_with: fossil_test_lib,
    include_directories: dir)

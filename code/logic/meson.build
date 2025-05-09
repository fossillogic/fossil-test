dir = include_directories('.')

test_code = ['mock.c', 'test.c', 'mark.c', 'sanity.c', 'common.c']

fossil_test_lib = library('pizza-test',
    test_code,
    install: true,
    include_directories: dir)

fossil_test_dep = declare_dependency(
    link_with: fossil_test_lib,
    include_directories: dir)

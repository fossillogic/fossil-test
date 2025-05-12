dir = include_directories('.')
cc = meson.get_compiler('c')

test_code = ['mock.c', 'test.c', 'mark.c', 'sanity.c', 'common.c']

fossil_test_lib = library('pizza-test',
    test_code,
    install: true,
    include_directories: dir,
    dependencies: [cc.find_library('m', required: false)])

fossil_test_dep = declare_dependency(
    link_with: fossil_test_lib,
    include_directories: dir)

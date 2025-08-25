dir = include_directories('.')
cc = meson.get_compiler('c')

test_code = ['mock.c', 'test.c', 'mark.c', 'sanity.c', 'common.c']

fossil_test_lib = library('pizza_test',
    test_code,
    install: true,
    include_directories: dir,
    dependencies: [cc.find_library('m', required: false)])

fossil_test_dep = declare_dependency(
    link_with: fossil_test_lib,
    include_directories: dir)

meson.override_dependency('fossil-test', fossil_test_dep)
meson.override_dependency('pizza-test', fossil_test_dep)
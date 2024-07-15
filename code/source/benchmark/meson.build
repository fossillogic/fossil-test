mark_code = ['benchmark.c']

fossil_mark_lib = library('fossil-mark',
    mark_code,
    install: true,
    include_directories: dir)

fossil_mark_dep = declare_dependency(
    link_with: fossil_mark_lib,
    include_directories: dir)
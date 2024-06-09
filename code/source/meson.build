code = files('module.c')

common_dep = dependency('fscl-xcommon-c')

lib = library('fscl-c',
    code,
    dependencies : common_dep,
    install: true,
    include_directories: dir)

fscl_c_dep = declare_dependency(
    link_with: lib,
    dependencies : common_dep,
    include_directories: dir)

code = files(
    # Fossil Test source
    'xtest.c',
    # Fossil Mock source
    'spy.c', 'fake.c',
    'stub.c', 'file.c',
    'behavior.c', 'inject.c',
    'network.c', 'output.c',
    'input.c', 'xmock.c'
)

common_dep = dependency('fscl-xcommon-c')

lib = library('fscl-c',
    code,
    dependencies : common_dep,
    install: true,
    include_directories: dir)

fossil_test_c_dep = declare_dependency(
    link_with: lib,
    dependencies : common_dep,
    include_directories: dir)

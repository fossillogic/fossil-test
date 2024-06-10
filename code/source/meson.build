test_code = [
    'unittest' / 'benchmark.c',
    'unittest' / 'commands.c',
    'unittest' / 'console.c',
    'unittest' / 'features.c',
    'unittest' / 'unittest.c']

fossil_test_lib = library('fossil-test',
    test_code,
    install: true,
    include_directories: dir)

fossil_test_dep = declare_dependency(
    link_with: fossil_test_lib,
    include_directories: dir)


mock_code = [
    'mockup' / 'spy.c',
    'mockup' / 'fake.c',
    'mockup' / 'stub.c',
    'mockup' / 'file.c',
    'mockup' / 'behavior.c',
    'mockup' / 'inject.c',
    'mockup' / 'network.c',
    'mockup' / 'output.c',
    'mockup' / 'input.c',
    'mockup' / 'mockup.c']

fossil_mock_lib = library('fossil-mock',
    mock_code,
    install: true,
    include_directories: dir)

fossil_mock_dep = declare_dependency(
    link_with: fossil_mock_lib,
    include_directories: dir)

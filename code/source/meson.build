test_code = [
    'unittest' / 'benchmark.c',
    'unittest' / 'commands.c',
    'unittest' / 'console.c',
    'unittest' / 'unittest.c']

fossil_test_lib = library('fossil-test',
    test_code,
    install: true,
    include_directories: dir)

fossil_test_dep = declare_dependency(
    link_with: fossil_test_lib,
    include_directories: dir)


mock_code = [
    'mockup' / 'mockup.c']

fossil_mock_lib = library('fossil-mock',
    mock_code,
    install: true,
    include_directories: dir)

fossil_mock_dep = declare_dependency(
    link_with: fossil_mock_lib,
    include_directories: dir)


mark_code = [
    'benchmark' / 'benchmark.c']

fossil_mark_lib = library('fossil-mark',
    mark_code,
    install: true,
    include_directories: dir)

fossil_mark_dep = declare_dependency(
    link_with: fossil_mark_lib,
    include_directories: dir)
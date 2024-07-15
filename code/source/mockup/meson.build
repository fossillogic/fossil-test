mock_code = ['mockup.c']

fossil_mock_lib = library('fossil-mock',
    mock_code,
    install: true,
    include_directories: dir)

fossil_mock_dep = declare_dependency(
    link_with: fossil_mock_lib,
    include_directories: dir)

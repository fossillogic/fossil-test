if get_option('with_test').enabled()
    run_command(['python3', 'tools' / 'generate-runner.py'], check: true)

    test_src = ['unit_runner.cpp']
    test_cubes = [
        'sample', 'bdd', 'tdd',
    ]

    foreach cube : test_cubes
        test_src += ['cases' / 'test_' + cube + '.c', 'cases' / 'test_' + cube + '.cpp']
    endforeach

    pizza = executable('testbed', test_src, include_directories: dir, dependencies: [fossil_test_dep])
    test('fossil_tests', pizza)  # Renamed the test target for clarity
endif

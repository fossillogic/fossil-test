if get_option('with_test').enabled()
    run_command(['python3', 'generate-runner.py'], check: true)

    test_src = ['xunit_runner.c']
    test_cubes = [
        'mocks', 'xfixture', 'bench', 'bdd', 'tdd', 'tags',
    ]

    foreach cube : test_cubes
        test_src += ['xtest_' + cube + '.c']
    endforeach

    pizza = executable('xcli', test_src, include_directories: dir, dependencies: [fossil_test_dep, fossil_mock_dep, fossil_mark_dep])
    test('fossil_tests', pizza)  # Renamed the test target for clarity
endif

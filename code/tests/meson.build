if get_option('with_test').enabled()
    run_command(['python3', 'tools' / 'generate-runner.py'], check: true)

    test_c   = ['unit_runner.c']
    test_cases = ['sample', 'bdd', 'tdd', 'ddd', 'mark', 'mock']

    foreach cases : test_cases
        test_c += ['cases' / 'test_' + cases + '.c']
        test_c += ['cases' / 'test_' + cases + '.cpp']
    endforeach

    pizza_c = executable('pizza', test_c, include_directories: dir, dependencies: [fossil_test_dep])

    test('fossil testing C', pizza_c)
endif
if get_option('with_test').enabled()
    run_command(['python3', 'tools' / 'generate-runner.py'], check: true)

    test_c   = ['unit_runner.c']
    test_cpp = ['unit_runner.cpp']
    test_cases = [
        'sample', 'bdd', 'tdd', 'ddd',
    ]

    foreach cases : test_cases
        test_c += ['cases' / 'test_' + cases + '.c']
        test_cpp += ['cases' / 'test_' + cases + '.cpp']
    endforeach

    pizza_c   = executable('testbed-c',   test_c,   include_directories: dir, dependencies: [fossil_test_dep])
    pizza_cpp = executable('testbed-cpp', test_cpp, include_directories: dir, dependencies: [fossil_test_dep])

    test('fossil testing C  ', pizza_c  )
    test('fossil testing Cpp', pizza_cpp)
endif

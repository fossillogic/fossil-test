if get_option('with_test').enabled()
    run_command(['python3', 'tools' / 'runner.py'], check: true)
    cards = run_command(['python3', 'tools' / 'wildcard.py'], check: true)

    test_cases = ['unit_runner.c', cards.stdout().strip().split('\n')]

    maip_c = executable('maip', test_cases, include_directories: dir, dependencies: [fossil_test_dep])

    test('fossil testing C', maip_c)
endif

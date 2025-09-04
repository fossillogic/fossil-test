if host_machine.system() == 'darwin'
    add_languages('objc', native: false, required: true)
    add_languages('objcpp', native: false, required: true)

    apple_dep = dependency('appleframeworks', modules : ['Foundation'])
endif

subdir('logic')
subdir('tests')
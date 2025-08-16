cpp = meson.get_compiler('cpp')
if cpp.has_define('__llvm_libcxx__')
  add_project_arguments('-D_LIBCPP_HARDENING_MODE=debug', language: 'cpp')
endif

subdir('logic')
subdir('tests')
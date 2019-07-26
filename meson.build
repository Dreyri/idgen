project(
  'idgen',
  'cpp',
  version: '0.1.0',
  license: 'MIT',
  meson_version: '>=0.48.0',
  default_options: [
    'cpp_std=c++17',
    'warning_level=3',
  ],
)

idgen_inc = include_directories('idgen')

idgen_dep = declare_dependency(
  include_directories: idgen_inc,
)

install_subdir('include/idg', install_dir: 'include')

pkgconfig = import('pkgconfig')
pkgconfig.generate(
  name: meson.project_name(),
  filebase: meson.project_name(),
  version: meson.project_version(),
  description: 'Efficiently generate unique global ids for types, without RTTI',
)

if get_option('tests')
  subdir('tests')
endif

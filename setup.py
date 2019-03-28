from distutils.core import setup, Extension

module1 = Extension('pyzzle',
                    include_dirs = ['/usr/local/include/SFML'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['pyzzle.cpp'])

setup (name = 'pyzzle',
       version = '1.0',
       description = 'This is a demo package',
       ext_modules = [module1])

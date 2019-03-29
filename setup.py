from distutils.core import setup, Extension

main = Extension('main',
                    include_dirs = ['/usr/local/include/SFML'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/main.cpp'])

spriteEngine = Extension('spriteEngine',
                    include_dirs = ['/usr/local/include/SFML'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/spriteEngine/spriteEngine.cpp'])

setup (name = 'pyzzle',
       version = '1.0',
       description = 'This is the pyzzle package',
       ext_modules = [main, spriteEngine])

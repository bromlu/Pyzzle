from distutils.core import setup, Extension

game = Extension('pyzzle.game',
                    include_dirs = ['/usr/local/include/SFML'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/game.cpp'])

spriteEngine = Extension('pyzzle.spriteEngine',
                    include_dirs = ['/usr/local/include/SFML'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/spriteEngine/spriteEngine.cpp'])

setup (name = 'pyzzle',
       version = '1.0',
       description = 'This is the pyzzle package',
       ext_modules = [game, spriteEngine])

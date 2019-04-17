import setuptools
from setuptools import setup, Extension, Command

game = Extension('pyzzle.game',
                    include_dirs = ['/usr/local/include/SFML', '/src/gameObject/', '/usr/local/opt/sfml/lib/'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/game.cpp', './src/gameObject/GameObject.cpp', './src/gameObject/Animation.cpp'])

sprites = Extension('pyzzle.sprites',
                    include_dirs = ['/usr/local/include/SFML', '/src/gameObject/', '/usr/local/opt/sfml/lib/'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/sprites/sprites.cpp', './src/gameObject/GameObject.cpp', './src/gameObject/Animation.cpp'])

animations = Extension('pyzzle.animations',
                    include_dirs = ['/usr/local/include/SFML', '/src/gameObject/', '/usr/local/opt/sfml/lib/'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/animations/animations.cpp', './src/gameObject/GameObject.cpp', './src/gameObject/Animation.cpp'])

input = Extension('pyzzle.input',
                    include_dirs = ['/usr/local/include/SFML', '/src/gameObject/', '/usr/local/opt/sfml/lib/'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/input/input.cpp', './src/gameObject/GameObject.cpp', './src/gameObject/Animation.cpp'])

tiles = Extension('pyzzle.tiles',
                    include_dirs = ['/usr/local/include/SFML', '/src/gameObject/', '/usr/local/opt/sfml/lib/'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/tiles/tiles.cpp', './src/gameObject/GameObject.cpp', './src/gameObject/Animation.cpp'])

setup (name = 'pyzzle',
       version = '1.0',
       description = 'This is the pyzzle package',
       ext_modules = [game, sprites, animations, input, tiles])

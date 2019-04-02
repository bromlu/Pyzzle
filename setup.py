import setuptools
from setuptools import setup, Extension, Command

game = Extension('pyzzle.game',
                    include_dirs = ['/usr/local/include/SFML', '/src/gameObject/'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/game.cpp', './src/gameObject/GameObject.cpp'])

sprites = Extension('pyzzle.sprites',
                    include_dirs = ['/usr/local/include/SFML', '/src/gameObject/'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/sprites/sprites.cpp', './src/gameObject/GameObject.cpp'])

setup (name = 'pyzzle',
       version = '1.0',
       description = 'This is the pyzzle package',
       ext_modules = [game, sprites])

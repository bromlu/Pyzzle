import setuptools
from setuptools import setup, Extension, Command

game = Extension('pyzzle.game',
                    include_dirs = ['/usr/local/include/SFML', '/src/gameObject/', '/usr/local/opt/sfml/lib/'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/game.cpp', './src/gameObject/GameObject.cpp', './src/gameObject/Animation.cpp'],
                    extra_compile_args = ["-std=c++11"])

sprites = Extension('pyzzle.sprites',
                    include_dirs = ['/usr/local/include/SFML', '/src/gameObject/', '/usr/local/opt/sfml/lib/'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/sprites/sprites.cpp', './src/gameObject/GameObject.cpp', './src/gameObject/Animation.cpp'],
                    extra_compile_args = ["-std=c++11"])

shapes = Extension('pyzzle.shapes',
                    include_dirs = ['/usr/local/include/SFML', '/src/gameObject/'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/shapes/shapes.cpp', './src/gameObject/GameObject.cpp', './src/gameObject/Animation.cpp'],
                    extra_compile_args = ["-std=c++11"])

animations = Extension('pyzzle.animations',
                    include_dirs = ['/usr/local/include/SFML', '/src/gameObject/', '/usr/local/opt/sfml/lib/'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/animations/animations.cpp', './src/gameObject/GameObject.cpp', './src/gameObject/Animation.cpp'],
                    extra_compile_args = ["-std=c++11"])

input = Extension('pyzzle.input',
                    include_dirs = ['/usr/local/include/SFML', '/src/gameObject/', '/usr/local/opt/sfml/lib/'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/input/input.cpp', './src/gameObject/GameObject.cpp', './src/gameObject/Animation.cpp'],
                    extra_compile_args = ["-std=c++11"])

audio = Extension('pyzzle.audio',
                    include_dirs = ['/usr/local/include/SFML', '/src/gameObject/'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system', '-lsfml-audio'],
                    sources = ['./src/audio/audio.cpp', './src/gameObject/GameObject.cpp', './src/gameObject/Animation.cpp'],
                    extra_compile_args = ["-std=c++11"])
                    
tiles = Extension('pyzzle.tiles',
                    include_dirs = ['/usr/local/include/SFML', '/src/gameObject/', '/usr/local/opt/sfml/lib/'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/tiles/tiles.cpp', './src/gameObject/GameObject.cpp', './src/gameObject/Animation.cpp'],
                    extra_compile_args = ["-std=c++11"])

collision = Extension('pyzzle.collision',
                    include_dirs = ['/usr/local/include/SFML', '/src/gameObject/'],
                    extra_link_args = ['-lsfml-graphics', '-lsfml-window', '-lsfml-system'],
                    sources = ['./src/collision/collision.cpp', './src/gameObject/GameObject.cpp'],
                    extra_compile_args = ["-std=c++11"])

setup (name = 'pyzzle',
       version = '1.0',
       description = 'This is the pyzzle package',
       ext_modules = [game, sprites, animations, input, collision, audio, tiles, shapes])

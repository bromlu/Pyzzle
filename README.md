# Pyzzle

Welcome to Pyzzle! A game engine for making 2D puzzle games using python!

## Installation

First, get python3 installed. It is available [on the official python site.](https://www.python.org/downloads/)

Then you'll need to install SFML, there are tutorials on how to do that [here.](https://www.sfml-dev.org/tutorials/2.5/)

After you have installed SFML, simply run make in the root directory in order to build and install the module.

```bash
$ make
```

To rebuild, run clean first to remove the build directory.

```bash
$ make clean
```

Note: if you make changes to the structure of the pyzzle package, then you will have to find where your python packages are and then delete the old version. If you don't do this, then when you import pyzzle it might import the old package, and not the updated one. As long as you don't make changes to setup.py though, this should never be an issue. Typically packages are installed here (for python3.7):

```bash
/Library/Frameworks/Python.framework/Versions/3.7/lib/python3.7/site-packages
```

## Structure

The main pyzzle module is called game, it stores all of the shared data and runs the game loop for you. **pyzzle.game MUST be imported before any other module is imported.** This is because all of the sub engines rely on the game module.

When importing, because pyzzle is a package, you cannot use "from pyzzle import *". You need to import each module separately.

```python
import pyzzle.game
import pyzzle.sprites
import pyzzle.tiles
```

When you call pyzzle.game.init() the pyzzle game engine calls
your init function then starts the game loop. The game loop calls the update and draw functions that you have
implemented in your code, just make sure that all of these functions are called init, update and draw and have no parameters, like this:

```python
def init():
    pass

def update():
    pass

def draw():
    pass
```

The update and draw functions are called 60 times a second, and all of your game code should be executed from inside these functions.

Another consideration is the fact that Pyzzle will import your game code in order to run these functions. With that in mind, make sure to wrap
your call to game.init in the following if statement.

```python
if __name__ == "__main__":
    pyzzle.game.init("MyGame", "My Game", 400, 400)
```

Basically, this just ensures that your code isn't run on the import, which would cause two copies of your game to open.

## Features

Pyzzle includes various features in order to help you with creating the perfect puzzle game.

### Currently implemented

- Animations (*Implementation in progress*)
- Input (*Implementation in progress*)
- Sprites (*Implementation in progress*)

### Future possibilities

- Audio engine
- Collision engine
- Drawing engine
- Event engine
- Physics engine
- Tile engine

### Game

```python
import pyzzle.game
```

The game module has the following functions.

| Function | Parameters | Returns | Purpose |
| :------: | :--------: | :-----: | :-----: |
| ```void init(string gameFileName, string gameName, int width, int height)``` | Filename of your main game file, name that appears on window, window width, window height | *None* | Creates the window and starts the game loop |
| ```long createGameObject()``` | *None* | Index of the new object | Creates a new game object |

### Animations

The animations module has the following functions.

| Function | Parameters | Returns | Purpose |
| :------: | :--------: | :-----: | :-----: |
| ```void play(long GameObjectIndex)``` | The index the game object is at | *None* | Cycles through the sprite sheet from left to right |

### Audio

- *TODO*

### Collision

- *TODO*

### Draw

- *TODO*

### Events

- *TODO*

### Input

```python
import pyzzle.input
```

The input module has the following functions.

| Function | Parameters | Returns | Purpose |
| :------: | :--------: | :-----: | :-----: |
| ```bool isKeyPressed(int keyIndex)``` | The index of the key according to [the SFML enum](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php) | A boolean answer | Check to see if a key is pressed or not |

### Physics

- *TODO*

### Sprites

```python
import pyzzle.sprites
```

The sprites module has the following functions.

| Function | Parameters | Returns | Purpose |
| :------: | :--------: | :-----: | :-----: |
| ```void addSprite(long GameObjectIndex, string imageName)``` | The index the game object is at, the name of the file the sprite sheet is in | *None* | Add a sprite to a game object |
| ```void setStartFrame(long GameObjectIndex, int left, int top, int width, int height)``` | The index the game object is at, the left location of the frame, the top location of the frame, the width of the frame, the height of the frame | *None* | Sets the frame of the sprite to be displayed |
| ```void draw(long GameObjectIndex)``` | The index the game object is at | *None* | Draws all of a game objects sprites |

### Tiles

- *TODO*

## Demos

Check out the demos folder to see five different puzzle games made using Pyzzle!

To run, simply execute the following command in the demo/x folder (where x is the demo you want to see).

```bash
$ python3 x.py
```

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
import pyzzle.spriteEngine
import pyzzle.tileEngine
```

When you call pyzzle.game.init() the pyzzle game engine starts the game loop. The game loop calls the update and draw functions that you have
implemented in your code, just make sure that they are called update and draw and have no parameters, like this:

```python
def update():
    pass

def draw():
    pass
```

These functions are called 60 times a second, and all of your game code should be executed from inside these functions.

Another consideration is the fact that Pyzzle will import your game code in order to run these functions. With that in mind, make sure to wrap
your initialization code in the following if statement.

```python
if __name__ == "__main__":
    pyzzle.game.init("MyGame", "My Game", 400, 400)
```

Basically, this just ensures that your code isn't run on the import, which would cause two copies of your game to open.

## Features

Pyzzle includes various features in order to help you with creating the perfect puzzle game.

### Currently implemented

- Sprite engine *Implementation in progress*

### Future possibilities

- Animation engine
- Audio engine
- Collision engine
- Event engine
- Input engine
- Physics engine
- Sprite engine
- Tile engine

### Game

The game module has the following functions available to you.

| Function | Parameters | Purpose | Example |
| :------: | :--------: | :-----: | :-----: |
| ```init(gameFileName, gameName, width, height)``` | (string) filename of your main game file, (string) name that appears on window, (int) window width, (int) window height | this function creates the window and starts the game loop | ```pyzzle.game.init("MyGame", "My Game", 400, 400)``` |

### Animation engine

- *TODO*

### Audio engine

- *TODO*

### Collision engine

- *TODO*

### Event engine

- *TODO*

### Input engine

- *TODO*

### Physics engine

- *TODO*

### Sprite engine

Currently the sprite engine just supports three functions for testing purposes.

makeSquare() --> makes a single square at location 20 20, and returns its index in the global rctangle vector.
moveSquare(x, y, index) --> moves the square at the given index to the given x y coordinate.
drawSquare(index) --> draws the square at the given index.

### Tile engine

- *TODO*

## Demos

Check out the demos folder to see five different puzzle games made using Pyzzle!

To run, simply execute the following command in the demo/x folder (where x is the demo you want to see).

```python
python3 x.py
```

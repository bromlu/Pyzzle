# Pyzzle

Welcome to Pyzzle! A game engine for making 2D puzzle games using python!

## Installation

First, get python3 installed. It is available [on the official python site.](https://www.python.org/downloads/)

Then you'll need to install SFML, there are tutorials on how to do that [here.](https://www.sfml-dev.org/tutorials/2.5/)

After you have installed SFML, run this command in the project root to build the python module.

```python
python3 setup.py build
```

Then install the module so that you can use it in your python game code.

```python
python3 setup.py install
```

## Structure

When you call pyzzle.init() the pyzzle game engine starts the game loop. The game loop calls the update and draw functions that you have
implemented in your code, just make sure that they are called update and draw and have no parameters, like this:

```python
def update():
    pass

def draw():
    pass
```

These functions are called 60 times a second, and all of your game code should be executed from inside these functions.

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

Currently the sprite engine just supports three functions.

makeSquare() --> makes a single square at location 20 20.
moveSquare(x, y) --> moves the implemented square to the given x y coordinate.
drawSquare() --> draws the square.

### Tile engine

- *TODO*

## Demos

Check out the demos folder to see five different puzzle games made using Pyzzle! 

To run, simply execute the following command in the demo/x folder (where x is the demo you want to see).

```python
python3 x.py
```

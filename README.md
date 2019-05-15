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

- Animations
- Audio
- Collision
- Game
- Input
- Shapes
- Sprites
- Tile
- Text

### Future possibilities

- Particle
- Physics

### Game

```python
import pyzzle.game
```

The game module has the following functions.

| Function | Parameters | Returns | Purpose |
| :------: | :--------: | :-----: | :-----: |
| ```void init(string gameFileName, string gameName, int width, int height)``` | Filename of your main game file, name that appears on window, window width, window height | *None* | Creates the window and starts the game loop |
| ```int createGameObject()``` | *None* | Index of the new object | Creates a new game object |
| ```void moveGameObject(int GameObjectIndex, float x, float y)``` | The index the game object is at, the x and the y coordinates | *None* | Moves the object by the specified amount |
| ```void setGameObjectPosition(int GameObjectIndex, float x, float y)``` | The index the game object is at, the x and the y coordinates | *None* | Sets the objects position to the specified coordinates |
| ```tuple getGameObjectPosition(int GameObjectIndex)``` | The index the game object is at | A tuple with 0 as x and 2 as y | returns the objects position |

### Animations

```python
import pyzzle.animations
```

The animations module has the following functions.

| Function | Parameters | Returns | Purpose |
| :------: | :--------: | :-----: | :-----: |
| ```void play(int gameObjectIndex, int AnimationIndex)``` | Index of the game object, index of the animation to play | *None* | Starts playing the given animation, stops any existing animations |
| ```void stop(int gameObjectIndex)``` | Index of the game object | *None* | Stops the objects animations |
| ```void pause(int gameObjectIndex)``` | Index of the game object | *None* | Pauses the objects animations at the current frame |
| ```void resume(int gameObjectIndex)``` | Index of the game object | *None* | Resumes the objects animations from where it was paused |
| ```void setDelay(int gameObjectIndex, int AnimationIndex, float delay)``` | Index of the game object, index of the animation, number of seconds to delay by | *None* | Sets the delay time between animation frames |
| ```int add(int gameObjectIndex)``` | Index of the game object | Index of the new animation | Creates a new animation object on the game object |
| ```void addFrame(int gameObjectIndex, int AnimationIndex, int x, int y, int width, int height)``` | Index of the game object, index of the animation, left location of frame, top location of frame, width of frame, height of frame | *None* | Add a single frame to the animation object |
| ```void addFrames(int gameObjectIndex, int AnimationIndex, int fromX, int fromY, int toX, int toY, int width, int height)``` | Index of the game object, index of the animation, left location of start frame, top location of start frame, left location of end frame, top location of end frame, width of frame, height of frame | *None* | Adds a set of frames between the start and stop point to the animation object |

### Audio

```python
import pyzzle.audio
```

| Function | Parameters | Returns | Purpose |
| :------: | :--------: | :-----: | :-----: |
| ```int loadMusic(string filename)``` | The filename of the music file | The index of the music | Loads music that can be played |
| ```void playMusic(int musicIndex)``` | Index of the music | *None* | Plays the music |
| ```void pauseMusic(int musicIndex)``` | Index of the music | *None* | Pauses the music |
| ```void stopMusic(int musicIndex)``` | Index of the music | *None* | Stops the music |
| ```void loopMusic(int musicIndex)``` | Index of the music | *None* | Tells the music to loop infinitely |
| ```int loadAudio(string filename)``` | The filename of the music file | Index of the new audio object | Loads audio that can be played |
| ```void playAudio(int audioIndex)``` | Index of the audio | *None* | Plays the audio |
| ```void pauseAudio(int audioIndex)``` | Index of the audio | *None* | Pauses the audio |
| ```void stopAudio(int audioIndex)``` | Index of the audio | *None* | Stops the audio |

### Collision

```python
import pyzzle.collision
```

| Function | Parameters | Returns | Purpose |
| :------: | :--------: | :-----: | :-----: |
| ```void addCollisionRect(int index, int left, int top, int width, int height, int scale = 0;)``` | Index of the game object to add collision rects to, left offset of rect, top offset of rect, width of rect, height of rect, scale of rect | *None* | Adds a collision rectangle to the game object |
| ```void drawCollisionObjects(int object)``` | Index of the game object | *None* | Draws the collision rects to the screen, mostly used for debugging |
| ```bool contains(int gameObject, float x, float y)``` | Index of the game object, x coordinate to check, y coordinate to check | True or False | Checks if the coordinates are in the game object |
| ```void collides(int gameObject1, int gameObject2)``` | Index of the first game object, index of the second game object | True or False | Checks if two game objects collide |
| ```void intersects(int gameObject, float x1, float y1, float x2, float y2)``` | Index of the game object, the start and end coordinates of a line | True or False | Checks if a line intersects with a gameObject |

### Input

```python
import pyzzle.input
```

The input module has the following functions.

| Function | Parameters | Returns | Purpose |
| :------: | :--------: | :-----: | :-----: |
| ```bool isKeyPressed(int keyIndex)``` | The index of the key according to [the SFML enum](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Keyboard.php) | A boolean answer | Check to see if a key is pressed or not |

### Shapes



### Sprites

```python
import pyzzle.sprites
```

The sprites module has the following functions.

| Function | Parameters | Returns | Purpose |
| :------: | :--------: | :-----: | :-----: |
| ```void add(int GameObjectIndex, string imageName)``` | The index the game object is at, the name of the file the sprite sheet is in | *None* | Add a sprite to a game object |
| ```void setFrame(int GameObjectIndex, int left, int top, int width, int height)``` | The index the game object is at, the left location of the frame, the top location of the frame, the width of the frame, the height of the frame | *None* | Sets the frame of the sprite to be displayed |
| ```void setScale(int GameObjectIndex, float x, float y)``` | The index the game object is at, the x scale factor, the y scale factor | *None* | Sets the scale of the sprite to be displayed |
| ```void draw(int GameObjectIndex)``` | The index the game object is at | *None* | Draws all of a game objects sprites |

### Text

```python
import pyzzle.text
```

The text module has the following functions. Note, draw will **not** work unless loadFonts has been successfully called.

| Function | Parameters | Returns | Purpose |
| :------: | :--------: | :-----: | :-----: |
| ```void loadFont(string fileName)``` | The name of the file the font is in | *None* | Loads the font to be used with text |
| ```void draw(string text, float x, float y, float weight = 30.0, int r = 255, int g = 255, int b = 255, int a = 255)``` | The text to display, the x and y coordinates to center the text around, the optional weight of the font, the optional color of the font | *None* | Draws text at the given location |

### Tiles

```python
import pyzzle.tiles
```

The tiles module has the following functions.

| Function | Parameters | Returns | Purpose |
| :------: | :--------: | :-----: | :-----: |
| ```void setTileWidth(float width)``` | The width you want all tiles to be | *None* | Sets the width of all tiles and scales the tilemap appropriately |
| ```void setTileHeight(float height)``` | The height you want all tiles to be | *None* | Sets the height of all tiles and scales the tilemap appropriately |
| ```void setTileFrame(int x, int y, int width, int height)``` | The upper left of the frame, the width and the height of the frame | *None* | Sets the section of the tilemap to be displayed |
| ```void addTextTileType(string filename)``` | The name of the file for the texture | *None* | Adds a tile that it represented by its index, i.e. the first tile you add is represented by a 0, the second a 1, and so on |
| ```void addPngTileType(string filename, int R, int G, int B)``` | The name of the file for the texture, the RGB values associated with this tile | *None* | Adds a tile that it represented by its color |
| ```void loadFromText(string filename, int width, int height)``` | The file to be loaded, the width and height of that file | *None* | Loads the given text file and translates it into a tilemap |
| ```void loadFromPng(string filename, int width, int height)``` | The file to be loaded, the width and height of that file | *None* | Loads the given PNG file and translates it into a tilemap |
| ```void draw()``` | *None* | *None* | Draws the tilemap |

The Tile subsystem allows you to load a tilemap with either text files or PNG files. Make sure to be consistent with what functions you use, if you mix and match the addTile functions and the loadFrom functions it will lead to undefined behavior.

## Demos

Check out the demos folder to see five different puzzle games made using Pyzzle!

To run, simply execute the following command in the demo/x folder (where x is the demo you want to see).

```bash
$ python3 x.py
```

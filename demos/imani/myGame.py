from pyzzle import game
from pyzzle import sprites
from pyzzle import animations
from pyzzle import input
from pyzzle import audio

from pyzzle import tiles

WIDTH = 1000
HEIGHT = 1000

mainCharacter = None
cameraX = 0
cameraY = 0

class MainCharacter:
    def __init__(self):
        self.index = game.createGameObject()
        game.setGameObjectPosition(self.index, 32, 0)
        sprites.add(self.index, "assets/bunny.png")
        sprites.setFrame(self.index, 0, 0, 32, 32)
        sprites.setScale(self.index, 2, 2)

        self.runUp = animations.add(self.index)
        self.runDown = animations.add(self.index)
        self.runRight = animations.add(self.index)
        self.runLeft = animations.add(self.index)

        animations.addFrames(self.index, self.runUp, 0, 32, 32, 32, 32, 32)
        animations.addFrames(self.index, self.runRight, 0, 64, 32, 64, 32, 32)
        animations.addFrames(self.index, self.runDown, 0, 0, 32, 0, 32, 32)
        animations.addFrames(self.index, self.runLeft, 0, 96, 32, 96, 32, 32)

        # collision.addCollisionRect(self.index, 0, 0, 32, 32, 3)

class Object:
    def __init__(self):
        self.index = game.createGameObject()
        game.setGameObjectPosition(self.index, 32, 0)
        sprites.add(self.index, "assets/carrot.png")
        sprites.setFrame(self.index, 500, 500, 32, 32)
        sprites.setScale(self.index, 5, 5)

if __name__ == "__main__":
    game.init("myGame", "Imani's Puzzle Game", WIDTH, HEIGHT)

def clampCamera(x):
    return x
    if x >= WIDTH:
        return WIDTH
    elif x <= 0:
        return 0
    else:
        return x

def init():
    tiles.addPngTileType("assets/grass.png", 255,255,255)
    tiles.addPngTileType("assets/reggrass.png",118,118,118)
    tiles.addPngTileType("assets/flower-grass.png",178,178,178)
    tiles.addPngTileType("assets/earth.png",0,0,0)
    tiles.setTileWidth(32)
    tiles.setTileHeight(32)
    tiles.loadFromPng("assets/farmMap.png", 32, 32)
    # tiles.setTileFrame(cameraX,cameraY,WIDTH,HEIGHT)
    tiles.setTileFrame(0,0,WIDTH,HEIGHT)
    global mainCharacter
    mainCharacter = MainCharacter()
    global carrot
    carrot = Object()
    
def update():
    move()
    
def draw(): 
    global mainCharacter
    global carrot
    tiles.draw()
    sprites.draw(mainCharacter.index)
    sprites.draw(carrot.index)

def collides():
    if tiles.objectInTile(mainCharacter.index, 150,150,150):
        return True
    return False

def move():
    global mainCharacter

    if input.isKeyPressed(22): #W
        game.moveGameObject(mainCharacter.index, 0, -5)
        animations.play(mainCharacter.index, mainCharacter.runUp)
    elif input.isKeyPressed(0): #A
        game.moveGameObject(mainCharacter.index, -5, 0)
        animations.play(mainCharacter.index, mainCharacter.runLeft)
    elif input.isKeyPressed(3): #D
        game.moveGameObject(mainCharacter.index, 5, 0)
        animations.play(mainCharacter.index, mainCharacter.runRight)
    elif input.isKeyPressed(18): #S
        game.moveGameObject(mainCharacter.index, 0, 5)
        animations.play(mainCharacter.index, mainCharacter.runDown)
    else:
        animations.stop(mainCharacter.index)

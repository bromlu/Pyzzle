from pyzzle import game
from pyzzle import sprites
from pyzzle import animations
from pyzzle import input
from pyzzle import shapes
from pyzzle import audio
from pyzzle import tiles

WIDTH = 800
HEIGHT = 800

mainCharacter = None
cameraX = 0
cameraY = 0

class MainCharacter:
    def __init__(self):
        self.index = game.createGameObject()
        game.setGameObjectPosition(self.index, WIDTH/2, HEIGHT/2)
        sprites.add(self.index, "MainCharacter.png")
        sprites.setFrame(self.index, 0, 64, 24, 32)
        sprites.setScale(self.index, 3, 3)

        self.runUp = animations.add(self.index)
        self.runDown = animations.add(self.index)
        self.runRight = animations.add(self.index)
        self.runLeft = animations.add(self.index)
        self.spin = animations.add(self.index)

        animations.addFrames(self.index, self.runUp, 0, 0, 552, 0, 24, 32)
        animations.addFrames(self.index, self.runRight, 0, 32, 552, 32, 24, 32)
        animations.addFrames(self.index, self.runDown, 0, 64, 552, 64, 24, 32)
        animations.addFrames(self.index, self.runLeft, 0, 96, 552, 96, 24, 32)

        animations.addFrame(self.index, self.spin, 0, 0, 24, 32)
        animations.addFrame(self.index, self.spin, 0, 32, 24, 32)
        animations.addFrame(self.index, self.spin, 0, 64, 24, 32)
        animations.addFrame(self.index, self.spin, 0, 96, 24, 32)

        animations.setDelay(self.index, self.runUp, 0.02)
        animations.setDelay(self.index, self.runRight, 0.02)
        animations.setDelay(self.index, self.runDown, 0.02)
        animations.setDelay(self.index, self.runLeft, 0.02)

        animations.play(self.index, self.spin)

if __name__ == "__main__":
    game.init("basicPuzzleGame", "Basic Puzzle Game", WIDTH, HEIGHT)

def clampCamera(x):
    return x
    if x >= WIDTH:
        return WIDTH
    elif x <= 0:
        return 0
    else:
        return x

def init():
    tiles.addPngTileType("black-marble.png", 255,255,255)
    tiles.addPngTileType("wood-tile.png",0,0,0)
    tiles.setTileWidth(50)
    tiles.setTileHeight(50)
    tiles.loadFromPng("map.png", 32,32)
    tiles.setTileFrame(cameraX,cameraY,WIDTH,HEIGHT)
    global mainCharacter
    mainCharacter = MainCharacter()
    audio.loadMusic("nice_music.ogg")
    audio.loadAudio("whistle.wav")
    audio.playMusic(0)
    audio.loopMusic(0)
    

def update(): 
    global mainCharacter
    global cameraX
    global cameraY
    if input.isKeyPressed(22): #W
        if(cameraY <= 0 or game.getGameObjectPosition(mainCharacter.index)[1] > HEIGHT/2):
            game.moveGameObject(mainCharacter.index, 0, -5)
        else:
            cameraY = clampCamera(cameraY-8)
        animations.play(mainCharacter.index, mainCharacter.runUp)
        audio.stopAudio(0)
    elif input.isKeyPressed(0): #A
        if(cameraX <= 0 or game.getGameObjectPosition(mainCharacter.index)[0] > WIDTH/2):
            game.moveGameObject(mainCharacter.index, -5, 0)
        else:
            cameraX = clampCamera(cameraX-8)
        animations.play(mainCharacter.index, mainCharacter.runLeft)
        audio.stopAudio(0)
    elif input.isKeyPressed(3): #D
        if(cameraX >= WIDTH or game.getGameObjectPosition(mainCharacter.index)[0] < WIDTH/2):
            game.moveGameObject(mainCharacter.index, 5, 0)
        else:
            cameraX = clampCamera(cameraX+8)
        animations.play(mainCharacter.index, mainCharacter.runRight)
        audio.stopAudio(0)
    elif input.isKeyPressed(18): #S
        if(cameraY >= WIDTH or game.getGameObjectPosition(mainCharacter.index)[1] < HEIGHT/2):
            game.moveGameObject(mainCharacter.index, 0, 5)
        else:
            cameraY = clampCamera(cameraY+8)
        animations.play(mainCharacter.index, mainCharacter.runDown)
        audio.stopAudio(0)
    else:
        animations.stop(mainCharacter.index)
        audio.playAudio(0)
    tiles.setTileFrame(cameraX,cameraY,WIDTH,HEIGHT)

def draw(): 
    global mainCharacter
    tiles.draw()
    sprites.draw(mainCharacter.index)
    shapes.drawCircle(200, 400, 400)

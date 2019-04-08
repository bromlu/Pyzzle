from pyzzle import game
from pyzzle import sprites
from pyzzle import animations
from pyzzle import input

WIDTH = 800
HEIGHT = 800

mainCharacter = None

class MainCharacter:
    def __init__(self):
        self.index = game.createGameObject()
        game.setGameObjectPosition(self.index, WIDTH/2, HEIGHT/2)
        sprites.add(self.index, "MainCharacter.png")
        sprites.setFrame(self.index, 0, 64, 24, 32)

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

        animations.play(self.index, self.runDown)
        animations.play(self.index, self.runDown)
        animations.stop(self.index, self.runDown)

if __name__ == "__main__":
    game.init("basicPuzzleGame", "Basic Puzzle Game", WIDTH, HEIGHT)

def init():
    global mainCharacter
    mainCharacter = MainCharacter()

def update(): 
    global mainCharacter
    if input.isKeyPressed(22): #W
        game.moveGameObject(mainCharacter.index, 0, -10)
        animations.play(mainCharacter.index, mainCharacter.runUpAnimation)
    if input.isKeyPressed(0): #A
        game.moveGameObject(mainCharacter.index, -10, 0)
        animations.play(mainCharacter.index, mainCharacter.runLeftAnimation)
    if input.isKeyPressed(3): #D
        game.moveGameObject(mainCharacter.index, 10, 0)
        animations.play(mainCharacter.index, mainCharacter.runRightAnimation)
    if input.isKeyPressed(18): #S
        game.moveGameObject(mainCharacter.index, 0, 10)
        animations.play(mainCharacter.index, mainCharacter.runDownAnimation)
    if not input.isKeyPressed(22) and not input.isKeyPressed(0) and not input.isKeyPressed(3) and not input.isKeyPressed(18) :
        animations.stop(mainCharacter.index, mainCharacter.runUpAnimation)

def draw(): 
    global mainCharacter
    sprites.draw(mainCharacter.index)
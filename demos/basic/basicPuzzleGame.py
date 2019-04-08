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
        sprites.setStartFrame(self.index, 0, 64, 24, 32)

        self.runUpAnimation = animations.add(self.index)
        self.runDownAnimation = animations.add(self.index)
        self.runRightAnimation = animations.add(self.index)
        self.runLeftAnimation = animations.add(self.index)

        animations.addFrame(self.index, self.runUpAnimation, 0, 64, 24, 32)
        animations.addFrames(self.index, self.runUpAnimation, 0, 0, 64, 64, 24, 32)

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
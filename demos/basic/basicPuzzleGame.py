from pyzzle import game
from pyzzle import sprites
from pyzzle import animations
from pyzzle import input

WIDTH = 800
HEIGHT = 800

gameObjects = { }

if __name__ == "__main__":
    game.init("basicPuzzleGame", "Basic Puzzle Game", WIDTH, HEIGHT)

def init():
    global gameObjects
    gameObjects["MainCharacter"] = game.createGameObject()
    sprites.addSprite(gameObjects["MainCharacter"], "MainCharacter.png")
    sprites.setStartFrame(gameObjects["MainCharacter"], 0, 64, 24, 32)
    game.setGameObjectPosition(gameObjects["MainCharacter"], WIDTH/2, HEIGHT/2)

def update(): 
    global gameObjects
    if input.isKeyPressed(22): #W
        sprites.setStartFrame(gameObjects["MainCharacter"], 0, 0, 24, 32)
        game.moveGameObject(gameObjects["MainCharacter"], 0, -10)
        animations.play(gameObjects["MainCharacter"])
    if input.isKeyPressed(0): #A
        sprites.setStartFrame(gameObjects["MainCharacter"], 0, 96, 24, 32)
        game.moveGameObject(gameObjects["MainCharacter"], -10, 0)
        animations.play(gameObjects["MainCharacter"])
    if input.isKeyPressed(3): #D
        sprites.setStartFrame(gameObjects["MainCharacter"], 0, 32, 24, 32)
        game.moveGameObject(gameObjects["MainCharacter"], 10, 0)
        animations.play(gameObjects["MainCharacter"])
    if input.isKeyPressed(18): #S
        sprites.setStartFrame(gameObjects["MainCharacter"], 0, 64, 24, 32)
        game.moveGameObject(gameObjects["MainCharacter"], 0, 10)
        animations.play(gameObjects["MainCharacter"])
    pass

def draw(): 
    global gameObjects
    sprites.draw(gameObjects["MainCharacter"])
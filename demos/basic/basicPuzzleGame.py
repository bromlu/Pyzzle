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
    gameObjects["MainCharacter"] = {}
    gameObjects["MainCharacter"]["index"] = game.createGameObject()
    sprites.addSprite(gameObjects["MainCharacter"]["index"], "MainCharacter.png")
    sprites.setStartFrame(gameObjects["MainCharacter"]["index"], 0, 64, 24, 32)
    game.setGameObjectPosition(gameObjects["MainCharacter"]["index"], WIDTH/2, HEIGHT/2)
    gameObjects["MainCharacter"]["RunUpAnimation"] = animations.addAnimation(gameObjects["MainCharacter"]["index"], 0)
    gameObjects["MainCharacter"]["RunRightAnimation"] = animations.addAnimation(gameObjects["MainCharacter"]["index"], 32)
    gameObjects["MainCharacter"]["RunDownAnimation"] = animations.addAnimation(gameObjects["MainCharacter"]["index"], 64)
    gameObjects["MainCharacter"]["RunLeftAnimation"] = animations.addAnimation(gameObjects["MainCharacter"]["index"], 96)

def update(): 
    global gameObjects
    if input.isKeyPressed(22): #W
        game.moveGameObject(gameObjects["MainCharacter"]["index"], 0, -10)
        animations.play(gameObjects["MainCharacter"]["index"], gameObjects["MainCharacter"]["RunUpAnimation"])
    if input.isKeyPressed(0): #A
        game.moveGameObject(gameObjects["MainCharacter"]["index"], -10, 0)
        animations.play(gameObjects["MainCharacter"]["index"], gameObjects["MainCharacter"]["RunLeftAnimation"])
    if input.isKeyPressed(3): #D
        game.moveGameObject(gameObjects["MainCharacter"]["index"], 10, 0)
        animations.play(gameObjects["MainCharacter"]["index"], gameObjects["MainCharacter"]["RunRightAnimation"])
    if input.isKeyPressed(18): #S
        game.moveGameObject(gameObjects["MainCharacter"]["index"], 0, 10)
        animations.play(gameObjects["MainCharacter"]["index"], gameObjects["MainCharacter"]["RunDownAnimation"])
    if not input.isKeyPressed(22) and not input.isKeyPressed(0) and not input.isKeyPressed(3) and not input.isKeyPressed(18) :
        animations.stop(gameObjects["MainCharacter"]["index"], gameObjects["MainCharacter"]["RunUpAnimation"])

def draw(): 
    global gameObjects
    sprites.draw(gameObjects["MainCharacter"]["index"])
from pyzzle import game
from pyzzle import sprites
from pyzzle import animations

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

def update(): 
    global gameObjects
    animations.play(gameObjects["MainCharacter"])
    pass

def draw(): 
    global gameObjects
    sprites.draw(gameObjects["MainCharacter"])
from pyzzle import game
from pyzzle import sprites

WIDTH = 800
HEIGHT = 800

gameObjects = { }

if __name__ == "__main__":
    game.init("basicPuzzleGame", "Basic Puzzle Game", WIDTH, HEIGHT)

def init():
    global gameObjects
    gameObjects["MainCharacter"] = game.createGameObject()
    sprites.addSprite(gameObjects["MainCharacter"], "MainCharacter.png")

def update(): 
    global gameObjects
    pass

def draw(): 
    global gameObjects
    sprites.draw(gameObjects["MainCharacter"])
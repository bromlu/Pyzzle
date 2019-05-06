import math
import random
from constants import WIDTH, HEIGHT
from pyzzle import game
from pyzzle import input
from pyzzle import sprites
from pyzzle import collision
from pyzzle import shapes
from pyzzle import text

player = None
SHIP_HEIGHT = 24
SHIP_WIDTH = 4
SHIP_SCALE = 3
SHIP_SPEED = 10

if __name__ == "__main__":
    text.loadFont("trench100free.otf")
    game.init("spaceExplorer", "Pyzzle Tech Demo", WIDTH, HEIGHT)

class Ship:
    def __init__(self):
        self.index = game.createGameObject()
        self.fuel = 100

def init():
    global player
    player = Ship()

def update():
    global player
   
    if input.isKeyPressed(73): #Up
        pass
    if input.isKeyPressed(74): #Down
        pass

def draw():
    global player
    sprites.draw(player.index)
    text.draw(str(player.fuel), 100, 100, 100)
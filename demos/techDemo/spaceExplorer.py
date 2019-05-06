import math
import random
from constants import WIDTH, HEIGHT
from pyzzle import game
from pyzzle import input
from pyzzle import sprites
from pyzzle import collision
from pyzzle import shapes
from pyzzle import text
from pyzzle import animations

player = None
SHIP_HEIGHT = 512
SHIP_WIDTH = 512
SHIP_SCALE = 0.5
SHIP_SPEED = 10

if __name__ == "__main__":
    text.loadFont("trench100free.otf")
    game.init("spaceExplorer", "Pyzzle Tech Demo", WIDTH, HEIGHT)

class Ship:
    def __init__(self):
        self.index = game.createGameObject()
        self.fuel = 100
        sprites.add(self.index, "spaceship.png")
        sprites.setFrame(self.index,0,0,SHIP_WIDTH,SHIP_HEIGHT)

        self.move = animations.add(self.index)
        self.die = animations.add(self.index)

        animations.addFrame(self.index, self.move, 512, 0, SHIP_WIDTH, SHIP_HEIGHT)
        animations.addFrame(self.index, self.move, 1024, 0, SHIP_WIDTH, SHIP_HEIGHT)
        animations.addFrame(self.index, self.move, 1536, 0, SHIP_WIDTH, SHIP_HEIGHT)
        animations.addFrame(self.index, self.move, 0, 512, SHIP_WIDTH, SHIP_HEIGHT)
        animations.addFrame(self.index, self.move, 512, 512, SHIP_WIDTH, SHIP_HEIGHT)
        animations.addFrame(self.index, self.move, 1024, 512, SHIP_WIDTH, SHIP_HEIGHT)
        animations.addFrame(self.index, self.move, 1536, 512, SHIP_WIDTH, SHIP_HEIGHT)
        animations.addFrame(self.index, self.move, 0, 1024, SHIP_WIDTH, SHIP_HEIGHT)

        animations.addFrame(self.index, self.die, 512, 1024, SHIP_WIDTH, SHIP_HEIGHT)
        animations.addFrame(self.index, self.die, 1024, 1024, SHIP_WIDTH, SHIP_HEIGHT)
        animations.addFrame(self.index, self.die, 1536, 1024, SHIP_WIDTH, SHIP_HEIGHT)
        animations.addFrame(self.index, self.die, 0, 1536, SHIP_WIDTH, SHIP_HEIGHT)
        animations.addFrame(self.index, self.die, 512, 1536, SHIP_WIDTH, SHIP_HEIGHT)
        animations.addFrame(self.index, self.die, 1024, 1536, SHIP_WIDTH, SHIP_HEIGHT)
        animations.addFrame(self.index, self.die, 1536, 1536, SHIP_WIDTH, SHIP_HEIGHT)

        animations.play(self.index, self.die)

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
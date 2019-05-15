# zombies. zombies everywhere. #

import math
import random
from pyzzle import game
from pyzzle import input
from pyzzle import sprites
from pyzzle import collision
from pyzzle import shapes
from pyzzle import text
from pyzzle import animations
from pyzzle import tiles
from pyzzle import audio

# globals #
blue = None
green = None
red = None
red2 = None

if __name__ == "__main__":
    game.init("zomb", "outbreak", 600, 400)

class Blob:
    def __init__(self, filename):
        self.speed = 3
        self.index = game.createGameObject()
        game.setGameObjectPosition(self.index, 300, 200)
        sprites.add(self.index, filename)
        sprites.setFrame(self.index,0,0,8,8)
        sprites.setScale(self.index, 8, 8)
        collision.addCollisionRect(self.index, 0,0,8*8,8*8)
        self.move = animations.add(self.index)
        animations.addFrame(self.index, self.move, 0, 0, 8, 8)
        animations.addFrame(self.index, self.move, 0, 8, 8, 8)

def init():
    global blue, green, red, red2
    blue = Blob("assets/blue.png")
    game.setGameObjectPosition(blue.index, 100, 200)
    green = Blob("assets/green.png")
    game.setGameObjectPosition(green.index, 200, 200)
    red = Blob("assets/red.png")
    game.setGameObjectPosition(red.index, 300, 200)
    red2 = Blob("assets/red.png")
    game.setGameObjectPosition(red2.index, 400, 200)
    # tiles.addPngTileType("assets/green.png", 255,255,255)
    # tiles.addPngTileType("assets/space.png",0,0,0)
    # tiles.setTileWidth(32)
    # tiles.setTileHeight(32)
    # tiles.loadFromPng("assets/map.png", 20, 12)
    # tiles.setTileFrame(0,0,600,400)

    # tiles.addPngTileType("assets/white.png", 255,255,255)
    # tiles.addPngTileType("assets/white.png", 165,165,165)
    # tiles.addPngTileType("assets/white.png", 80,124,159)
    # tiles.addPngTileType("assets/white.png", 159,139,80)
    # tiles.addPngTileType("assets/space.png",0,0,0)
    # tiles.setTileWidth(32)
    # tiles.setTileHeight(32)
    # tiles.loadFromPng("assets/map.png", 150,150)
    # tiles.setTileFrame(0,0,600,400)


def update():
    if input.isKeyPressed(73): # up
        game.moveGameObject(blue.index, 0, -blue.speed)
        if collision.collides(blue.index, green.index): # or tiles.objectInTile(blue.index, 0, 0, 0):
            game.moveGameObject(blue.index, 0, blue.speed)
        elif collision.collides(blue.index, red.index):
            game.moveGameObject(red.index, 0, -blue.speed)
    if input.isKeyPressed(74): # down
        game.moveGameObject(blue.index, 0, blue.speed)
        if collision.collides(blue.index, green.index): #  or tiles.objectInTile(blue.index, 0, 0, 0):
            game.moveGameObject(blue.index, 0, -blue.speed)
        elif collision.collides(blue.index, red.index):
            game.moveGameObject(red.index, 0, blue.speed)
    if input.isKeyPressed(71): # left
        game.moveGameObject(blue.index, -blue.speed, 0)
        if collision.collides(blue.index, green.index): #  or tiles.objectInTile(blue.index, 0, 0, 0):
            game.moveGameObject(blue.index, blue.speed, 0)
        elif collision.collides(blue.index, red.index):
            game.moveGameObject(red.index, -blue.speed, 0)
    if input.isKeyPressed(72): # right
        game.moveGameObject(blue.index, blue.speed, 0)
        if collision.collides(blue.index, green.index): #  or tiles.objectInTile(blue.index, 0, 0, 0):
            game.moveGameObject(blue.index, -blue.speed, 0)
        elif collision.collides(blue.index, red.index):
            game.moveGameObject(red.index, blue.speed, 0)
    animations.play(blue.index, blue.move)
    animations.play(green.index, green.move)
    animations.play(red.index, red.move)

def draw():
    tiles.draw()
    sprites.draw(green.index)
    sprites.draw(red.index)
    # sprites.draw(red2.index)
    sprites.draw(blue.index)

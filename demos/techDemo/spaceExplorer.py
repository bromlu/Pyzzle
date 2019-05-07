import math
import random
from constants import WIDTH, HEIGHT, TILE_WIDTH, TILE_HEIGHT
from pyzzle import game
from pyzzle import input
from pyzzle import sprites
from pyzzle import collision
from pyzzle import shapes
from pyzzle import text
from pyzzle import animations
from pyzzle import tiles

player = None
beacon = None
deadAnimationFrameCount = 0
beaconActivatedFrameCount = 0
currentLevel = 0
levels = [
    (0,0,WIDTH,HEIGHT),
    (50*TILE_WIDTH,0,WIDTH,HEIGHT),
    (0,50*TILE_HEIGHT,WIDTH,HEIGHT),
    (50*TILE_WIDTH,50*TILE_HEIGHT,WIDTH,HEIGHT)
]
SHIP_HEIGHT = 512
SHIP_WIDTH = 512
SHIP_SCALE = 0.25
SHIP_SPEED = 10

if __name__ == "__main__":
    text.loadFont("trench100free.otf")
    game.init("spaceExplorer", "Pyzzle Tech Demo", WIDTH, HEIGHT)

class Beacon:
    def __init__(self):
        self.index = game.createGameObject()
        self.width = SHIP_WIDTH * SHIP_SCALE
        self.height = SHIP_HEIGHT * SHIP_SCALE
        game.setGameObjectPosition(self.index, WIDTH / 2, SHIP_HEIGHT * SHIP_SCALE)
        sprites.add(self.index, "beacon.png")
        sprites.setFrame(self.index,0,SHIP_HEIGHT,SHIP_WIDTH,SHIP_HEIGHT)
        sprites.setScale(self.index, SHIP_SCALE, SHIP_SCALE)
        collision.addCollisionRect(self.index, int(self.width / 4), int(self.width / 4), int(self.width / 2), int(self.height / 2))

class Ship:
    def __init__(self):
        self.width = SHIP_WIDTH * SHIP_SCALE
        self.height = SHIP_HEIGHT * SHIP_SCALE
        self.index = game.createGameObject()
        game.setGameObjectPosition(self.index, WIDTH/2 - self.width / 2, HEIGHT - self.height)
        self.fuel = 100
        self.dead = False
        self.won = False
        self.vx = 0
        self.vy = 0

        collision.addCollisionRect(self.index, int(self.width/2 - 10), 12, int(self.width / 8), int(self.height / 4))
        collision.addCollisionRect(self.index, 10, 15 + int(self.height / 4), int(self.width - 20), int(self.height / 4))
        sprites.add(self.index, "spaceship.png")
        sprites.setFrame(self.index,0,0,SHIP_WIDTH,SHIP_HEIGHT)
        sprites.setScale(self.index, SHIP_SCALE, SHIP_SCALE)

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

def init():
    global player
    global beacon
    player = Ship()
    beacon = Beacon()
    tiles.addPngTileType("aestroid_brown.png", 255,255,255)
    tiles.addPngTileType("aestroid_dark.png", 165,165,165)
    tiles.addPngTileType("aestroid_gray_2.png", 80,124,159)
    tiles.addPngTileType("aestroid_gray.png", 159,139,80)
    tiles.addPngTileType("space.jpg",0,0,0)
    tiles.setTileWidth(TILE_WIDTH)
    tiles.setTileHeight(TILE_HEIGHT)
    tiles.loadFromPng("map.png", 100,100)
    tiles.setTileFrame(0,0,WIDTH,HEIGHT)

def update():
    global player
    global deadAnimationFrameCount
    global beaconActivatedFrameCount
    global currentLevel
    global levels

    if not player.dead and not player.won:
        if not input.isKeyPressed(73):
            animations.stop(player.index)
            sprites.setFrame(player.index,0,0,SHIP_WIDTH,SHIP_HEIGHT)
        if input.isKeyPressed(73) and player.fuel > 0: #Up
            animations.play(player.index, player.move)
            player.vy -= 1
            player.fuel -= 1
        if input.isKeyPressed(74) and player.fuel > 0: #Down
            player.vy += 1
            player.fuel -= 1
        if input.isKeyPressed(71) and player.fuel > 0: #Left
            player.vx -= 1
            player.fuel -= 1
        if input.isKeyPressed(72) and player.fuel > 0: #Right
            player.vx += 1
            player.fuel -= 1
    elif deadAnimationFrameCount == 35 or beaconActivatedFrameCount == 35:
        if player.won:
            currentLevel+=1
            if currentLevel == len(levels):
                currentLevel = 0
            tiles.setTileFrame(*levels[currentLevel])
        game.setGameObjectPosition(player.index, WIDTH/2 - SHIP_WIDTH * SHIP_SCALE / 2, HEIGHT - player.height)
        sprites.setFrame(beacon.index,0,SHIP_HEIGHT,SHIP_WIDTH,SHIP_HEIGHT)
        animations.stop(player.index)
        player.dead = False
        player.won = False
        player.fuel = 100
        deadAnimationFrameCount = 0
        beaconActivatedFrameCount = 0
    elif player.dead:
        deadAnimationFrameCount += 1
    elif player.won:
        beaconActivatedFrameCount += 1


    game.moveGameObject(player.index, player.vx, player.vy)

    playerPosition = game.getGameObjectPosition(player.index)
    centerX = playerPosition[0] + (player.width / 2)
    centerY = playerPosition[1] + (player.height / 2)
    if (tiles.pointInTile(centerX, centerY, 255, 255, 255) or tiles.pointInTile(centerX, centerY, 165,165,165) or 
            tiles.pointInTile(centerX, centerY,80,124,159) or tiles.pointInTile(centerX, centerY, 159,139,80) or 
            centerX < 0 or centerX > WIDTH or centerY < 0 or centerY > HEIGHT):
        player.dead = True
        player.vx = 0
        player.vy = 0
        animations.play(player.index, player.die)
    if player.vx == 0 and player.vy == 0 and player.fuel == 0:
        game.setGameObjectPosition(player.index, WIDTH/2 - player.width / 2, HEIGHT - player.height)
        animations.stop(player.index)
        player.fuel = 100

    if collision.collides(beacon.index, player.index):
        sprites.setFrame(beacon.index,0,0,SHIP_WIDTH,SHIP_HEIGHT)
        animations.stop(player.index)
        player.won = True
        player.vx = 0
        player.vy = 0

def draw():
    global player
    global beacon
    tiles.draw()
    text.draw("Fuel", 150, 50, 100, 104, 255, 0)
    text.draw(str(player.fuel), 300, 50, 100, 104, 255, 0)
    sprites.draw(beacon.index)
    sprites.draw(player.index)
    collision.drawCollisionObjects(player.index)
    collision.drawCollisionObjects(beacon.index)
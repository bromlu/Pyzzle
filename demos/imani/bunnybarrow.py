import random
import time

from pyzzle import game
from pyzzle import sprites
from pyzzle import animations
from pyzzle import input
from pyzzle import audio
from pyzzle import shapes
from pyzzle import collision
from pyzzle import text
from pyzzle import tiles

WIDTH = 800
HEIGHT = 800

menuItems = []
currentlySelected = 0
start = time.time()
dig = False
carrotTimer = 0
minTime = 50
right = bool
hurtSound = None

mainCharacter = None
shovelTimer = 0
carrots = []
rocks = []
score = 0
health = 3

if __name__ == "__main__":
    text.loadFont("assets/Kylie-Jeslyn.otf")
    game.init("bunnybarrow", "BunnyBarrow", WIDTH, HEIGHT)

#Menu
class MenuItem:
    def __init__(self, text, x, y, w, action):
        self.text = text
        self.x = x
        self.y = y
        self.w = w
        self.selected = False
        self.action = action

    def draw(self):
        if self.selected:
            text.draw(self.text, self.x, self.y, self.w, 50, 50, 0)
        else:
            text.draw(self.text, self.x, self.y, self.w)
def init():
    global menuItems
    global currentlySelected
    global hurtSound
    menuItems = []
    currentlySelected = 0
    menuItems.append(MenuItem("play", WIDTH/2, HEIGHT/2 - 50, 50, gotoGame))
    menuItems[currentlySelected].selected = True
    hurtSound = audio.loadAudio("assets/hurt.wav")

def update():
    global menuItems
    global currentlySelected
    global start

    if time.time() - start < 0.095:
        return
    start = time.time()

    if input.isKeyPressed(18) or input.isKeyPressed(74): #S and Down
        menuItems[currentlySelected].selected = False
        currentlySelected = currentlySelected + 1
        if currentlySelected >= len(menuItems):
            currentlySelected = 0
        menuItems[currentlySelected].selected = True
    if input.isKeyPressed(22) or input.isKeyPressed(73): #W and Up
        menuItems[currentlySelected].selected = False
        currentlySelected = currentlySelected - 1
        if currentlySelected < 0:
            currentlySelected = len(menuItems) - 1
        menuItems[currentlySelected].selected = True
    if input.isKeyPressed(58): # Enter
        menuItems[currentlySelected].action()


def draw():
    text.draw("Bunny Barrow!", WIDTH/2, 100.0, 100.0)
    for item in menuItems:
        item.draw()
def end_draw():
    global score
    text.draw("score: " + str(score), WIDTH/2, 100.0, 50.0)
    text.draw("press enter to play again", WIDTH/2, 300.0, 25.0)

def end_update():
    if input.isKeyPressed(58): # Enter
        gotoGame()

def gotoGame():
    game.switchState("bunnybarrow", "game_init", "game_update", "game_draw")

def gotoMenu():
    game.switchState("bunnybarrow", "init", "update", "draw")

def gotoEnd():
    game.switchState("bunnybarrow", "", "end_update", "end_draw")

class MainCharacter:
    def __init__(self):
        self.index = game.createGameObject()
        self.shovelRIndex = game.createGameObject()  
        self.shovelLIndex = game.createGameObject()  
        self.barrowIndex = game.createGameObject() 
        self.barrow1Index = game.createGameObject() 
        
        game.setGameObjectPosition(self.index, 0, 720)
        game.setGameObjectPosition(self.shovelRIndex, 64, 720)
        game.setGameObjectPosition(self.shovelLIndex, 64, 720)
        game.setGameObjectPosition(self.barrowIndex, 64, 720)
        game.setGameObjectPosition(self.barrow1Index, -64, 720)
       
        collision.addCollisionRect(self.index, 6, 10, 20, 21, 3)
        collision.addCollisionRect(self.shovelRIndex, 20, 20, 5, 10, 3)
        collision.addCollisionRect(self.shovelLIndex, 0, 20, 5, 10, 3)
        collision.addCollisionRect(self.barrowIndex, 5, 10, 20, 5, 3)
        collision.addCollisionRect(self.barrow1Index, 5, 10, 20, 5, 3)
        
        sprites.add(self.index, "assets/bunny.png")
        sprites.add(self.shovelRIndex, "assets/shovelR.png")
        sprites.add(self.shovelLIndex, "assets/shovelL.png")
        sprites.add(self.barrowIndex, "assets/barrowR.png")
        sprites.add(self.barrow1Index, "assets/barrowL.png")
        
        sprites.setFrame(self.index, 0, 0, 32, 32)
        sprites.setFrame(self.shovelRIndex, 0, 0, 32, 32)
        sprites.setFrame(self.shovelLIndex, 0, 0, 32, 32)
        sprites.setFrame(self.barrowIndex, 0, 0, 32, 32)
        sprites.setFrame(self.barrow1Index, 0, 0, 32, 32)
        
        sprites.setScale(self.index, 3, 3)
        sprites.setScale(self.shovelRIndex, 3, 3)
        sprites.setScale(self.shovelLIndex, 3, 3)
        sprites.setScale(self.barrowIndex, 3, 3)
        sprites.setScale(self.barrow1Index, 3, 3)

        self.runRight = animations.add(self.index)
        self.runLeft = animations.add(self.index)
        self.digR = animations.add(self.shovelRIndex)
        self.digL = animations.add(self.shovelLIndex)

        animations.addFrames(self.index, self.runRight, 0, 32, 32, 32, 32, 32)
        animations.addFrames(self.index, self.runLeft, 0, 64, 32, 64, 32, 32)
        animations.addFrames(self.shovelRIndex, self.digR, 0, 0, 0, 32, 32, 32)
        animations.addFrames(self.shovelLIndex, self.digL, 0, 0, 0, 32, 32, 32)

class Carrot:
    def __init__(self):
        self.index = game.createGameObject()
        self.vy = random.randint(3, 6)
        game.setGameObjectPosition(self.index, random.randrange(0,WIDTH-32), 0)
        collision.addCollisionRect(self.index, 10, 7, 12, 15, 3)
        sprites.add(self.index, "assets/carrot.png")
        sprites.setFrame(self.index, 0, 0, 32, 32)
        sprites.setScale(self.index, 3, 3)

class Rock:
    def __init__(self):
        self.index = game.createGameObject()
        self.vy = random.randint(5, 10)
        game.setGameObjectPosition(self.index, random.randrange(0,WIDTH-32), 0)
        collision.addCollisionRect(self.index, 10, 7, 12, 15, 3)
        sprites.add(self.index, "assets/rock.png")
        sprites.setFrame(self.index, 0, 0, 32, 32)
        sprites.setScale(self.index, 3, 3)


def game_init():
    global health
    global mainCharacter 
    global score
    global carrots
    global rocks
    global shovelTimer
    global minTime
    tiles.addPngTileType("assets/texture2.png", 255,255,255)
    tiles.addPngTileType("assets/texture1.png", 204,204,204)
    tiles.addPngTileType("assets/reggrass.png", 150,150,150)
    tiles.addPngTileType("assets/grass.png", 111,111,111)
    tiles.addPngTileType("assets/earth.png", 0,0,0)
    tiles.addPngTileType("assets/flower-grass.png", 88,88,88)
    tiles.setTileWidth(32)
    tiles.setTileHeight(32)
    tiles.loadFromPng("assets/backgroundMap1.png", 32, 32)
    tiles.setTileFrame(0,0,WIDTH,HEIGHT)
    mainCharacter = MainCharacter()
    score = 0
    health = 3
    shovelTimer = 0
    carrots = []
    rocks = []
    minTime = 0
    

def game_update():
    move()
    spawn()
    drop()

def game_draw():
    global mainCharacter
    global carrots
    global score
    global dig
    global right
    tiles.draw()
    sprites.draw(mainCharacter.index)
    # sprites.draw(mainCharacter.barrowIndex)

    # collision.drawCollisionObjects(mainCharacter.shovelRIndex)
    # collision.drawCollisionObjects(mainCharacter.shovelLIndex)
    # collision.drawCollisionObjects(mainCharacter.barrowIndex)
    # collision.drawCollisionObjects(mainCharacter.barrow1Index)
    # collision.drawCollisionObjects(mainCharacter.index)

    
    if right:
        if dig:
            sprites.draw(mainCharacter.shovelRIndex)
        else:
            sprites.draw(mainCharacter.barrowIndex)
    else: 
        if dig:
            sprites.draw(mainCharacter.shovelLIndex)
        else:
            sprites.draw(mainCharacter.barrow1Index)

    for i in range(len(carrots)):
        sprites.draw(carrots[i].index)
    for i in range(len(rocks)):
        sprites.draw(rocks[i].index)

        # collision.drawCollisionObjects(carrots[i].index)
    text.draw(str(score), 100, 100, 50)
    text.draw(str(health), 100, 50, 50)
    # text.draw(str(minTime), 400, 300, 50)

def move():
    global mainCharacter
    global dig
    global right
    global shovelTimer
    dig = False
    if input.isKeyPressed(18): #s
        pos = game.getGameObjectPosition(mainCharacter.index)
        shovelTimer += 1
        if right:
            game.setGameObjectPosition(mainCharacter.shovelRIndex, pos[0], pos[1])
            animations.play(mainCharacter.shovelRIndex, mainCharacter.digR)
        else:
            game.setGameObjectPosition(mainCharacter.shovelLIndex, pos[0], pos[1])
            animations.play(mainCharacter.shovelLIndex, mainCharacter.digL)
        dig = True
    else:
        shovelTimer = 0
        animations.stop(mainCharacter.shovelRIndex)
        animations.stop(mainCharacter.shovelLIndex)
        if input.isKeyPressed(0): #A
            if inbounds(-5) == True:
                game.moveGameObject(mainCharacter.index, -5, 0)
                game.moveGameObject(mainCharacter.barrowIndex, -5, 0)
                game.moveGameObject(mainCharacter.barrow1Index, -5, 0)
                animations.play(mainCharacter.index, mainCharacter.runLeft)
                right = False
        elif input.isKeyPressed(3): #D
            if inbounds(96) == True:
                game.moveGameObject(mainCharacter.index, 5, 0)
                game.moveGameObject(mainCharacter.barrowIndex, 5, 0)
                game.moveGameObject(mainCharacter.barrow1Index, 5, 0)
                animations.play(mainCharacter.index, mainCharacter.runRight)
                right = True
        else:
            # pass
            animations.stop(mainCharacter.index)
        
def inbounds(direction):
    global mainCharacter
    if direction < 0:
        return game.getGameObjectPosition(mainCharacter.index)[0] + direction > 0
    else:
        return game.getGameObjectPosition(mainCharacter.index)[0] + direction < WIDTH



def spawn():
    #creates new carrots and adds them to the list
    global carrots
    global rocks
    global carrotTimer
    global minTime
    if carrotTimer <= 0:
        carrotTimer = random.randint(int(minTime), 50)
        carrot = Carrot()
        carrots.append(carrot)
        minTime *= .9
        if random.randint(0, 1) == 0:
            rock = Rock()
            rocks.append(rock)
    carrotTimer -= 1

def drop():
    #updates the x,y position of the carrots by itterating through list
    global carrots
    global rocks
    global mainCharacter
    global health
    global score
    global dig
    for carrot in carrots:
        #check if bunny catches
       
        if right:
            if dig and shovelTimer > 10:
                if collision.collides(mainCharacter.shovelRIndex, carrot.index):
                    carrots.remove(carrot)
                    score += 1
            elif collision.collides(mainCharacter.barrowIndex, carrot.index):
                carrots.remove(carrot)
                score += 1
        else:
            if dig and shovelTimer > 10:
                if collision.collides(mainCharacter.shovelLIndex, carrot.index):
                    carrots.remove(carrot)
                    score += 1
            elif collision.collides(mainCharacter.barrow1Index, carrot.index):
                carrots.remove(carrot)
                score += 1
        #check if hit floor
        if not game.getGameObjectPosition(carrot.index)[1] > 755:
            game.moveGameObject(carrot.index, 0, carrot.vy)

    for rock in rocks:
        game.moveGameObject(rock.index, 0, rock.vy)
        if collision.collides(mainCharacter.index, rock.index):
            health -= 1
            if health <= 0:
                gotoEnd()
            rocks.remove(rock)
            audio.stopAudio(hurtSound)
            audio.playAudio(hurtSound)
        if game.getGameObjectPosition(carrot.index)[1] > 810:
            rocks.remove(rock)     
# TODO: fix spawn, resprite - barrow, background, gamestates, music, fix collisionrect

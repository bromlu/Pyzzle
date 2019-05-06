import time
from constants import WIDTH, HEIGHT
from pyzzle import game
from pyzzle import text
from pyzzle import input

menuItems = []
currentlySelected = 0
start = time.time()

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
            text.draw(self.text, self.x, self.y, self.w, 102, 204, 0)
        else:
            text.draw(self.text, self.x, self.y, self.w)

def gotoHome():
    game.switchState("menu", "init", "update", "draw")

def gotoPlay():
    game.switchState("menu", "initPlay", "update", "draw")

def gotoAbout():
    game.switchState("menu", "initText", "update", "drawAbout")

def gotoThanks():
    game.switchState("menu", "initText", "update", "drawThanks")

def gotoPong():
    game.switchState("pong", "init", "update", "draw")

if __name__ == "__main__":
    text.loadFont("trench100free.otf")
    game.init("menu", "Pyzzle Tech Demo", WIDTH, HEIGHT)

def init():
    global menuItems
    global currentlySelected
    menuItems = []
    currentlySelected = 0
    menuItems.append(MenuItem("Play", WIDTH/2, HEIGHT/2 - 100, 72.0, gotoPlay))
    menuItems.append(MenuItem("About", WIDTH/2, HEIGHT/2, 72.0, gotoAbout))
    menuItems.append(MenuItem("Thanks", WIDTH/2, HEIGHT/2 + 100, 72.0, gotoThanks))
    menuItems[currentlySelected].selected = True

def initPlay():
    global menuItems
    global currentlySelected
    menuItems = []
    currentlySelected = 0
    menuItems.append(MenuItem("Pong", WIDTH/2, HEIGHT/2 - 100, 72.0, gotoPong))
    menuItems.append(MenuItem("Space Explorer", WIDTH/2, HEIGHT/2, 72.0, gotoHome))
    menuItems.append(MenuItem("Back", WIDTH/2, HEIGHT/2 + 100, 72.0, gotoHome))
    menuItems[currentlySelected].selected = True

def initText():
    global menuItems
    global currentlySelected
    menuItems = []
    currentlySelected = 0
    menuItems.append(MenuItem("Back", WIDTH/2, HEIGHT - 100, 72.0, gotoHome))
    menuItems[currentlySelected].selected = True

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

def drawMenu():
    text.draw("Pyzzle Tech Demo", WIDTH/2, 100.0, 148.0)
    for item in menuItems:
        item.draw()

def draw():
    drawMenu()

def drawAbout():
    text.draw("This tech demo is meant to demostrate\n the capabilities of the Pyzzle game engine.", WIDTH + 30, HEIGHT/2, 72.0)
    drawMenu()

def drawThanks():
    text.draw("Special Thanks to Imani, Caitlin, and Tim \n      for being great teammates.", WIDTH, HEIGHT/2, 72.0)
    drawMenu()
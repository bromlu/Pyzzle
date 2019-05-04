import time
from pyzzle import game
from pyzzle import text
from pyzzle import input

WIDTH = 1600
HEIGHT = 1200

menuItems = []
currentlySelected = 0
start = time.time()

class MenuItem:
    def __init__(self, text, x, y, w):
        self.text = text
        self.x = x
        self.y = y
        self.w = w
        self.selected = False

    def draw(self):
        if self.selected:
            text.draw(self.text, self.x, self.y, self.w, 102, 204, 0)
        else:
            text.draw(self.text, self.x, self.y, self.w)

if __name__ == "__main__":
    game.init("menu", "Pyzzle Tech Demo", WIDTH, HEIGHT)

def init():
    global menuItems
    global currentlySelected
    text.loadFont("trench100free.otf")
    menuItems.append(MenuItem("Play", WIDTH/2, HEIGHT/2 - 100, 72.0))
    menuItems.append(MenuItem("About", WIDTH/2, HEIGHT/2, 72.0))
    menuItems.append(MenuItem("Thanks", WIDTH/2, HEIGHT/2 + 100, 72.0))
    menuItems[currentlySelected].selected = True

def update():
    global menuItems
    global currentlySelected
    global start

    if time.time() - start < 0.095:
        return
    start = time.time()

    if input.isKeyPressed(18) or input.isKeyPressed(74): #S
        menuItems[currentlySelected].selected = False
        currentlySelected = currentlySelected + 1
        if currentlySelected >= len(menuItems):
            currentlySelected = 0
        menuItems[currentlySelected].selected = True
    if input.isKeyPressed(22) or input.isKeyPressed(73): #W
        menuItems[currentlySelected].selected = False
        currentlySelected = currentlySelected - 1
        if currentlySelected < 0:
            currentlySelected = len(menuItems) - 1
        menuItems[currentlySelected].selected = True

def draw():
    text.draw("Welcome to the Pyzzle tech demo!", WIDTH/2, 100.0, 72.0)
    for item in menuItems:
        item.draw()
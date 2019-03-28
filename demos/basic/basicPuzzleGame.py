import pyzzle
import datetime

pyzzle.init("basicPuzzleGame", "Basic Puzzle Game")
pyzzle.makeSquare()

x = 0.0
y = 0.0

def update(): 
    global x
    global y

    x += 2.0
    y += 2.0

    if(x > 400): 
        x = 0.0
        y = 0.0

    pyzzle.moveSquare(x, y)

def draw(): 
    pyzzle.drawSquare()

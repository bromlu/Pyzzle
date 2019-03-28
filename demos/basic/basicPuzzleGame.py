import pyzzle
import datetime

WIDTH = 800
HEIGHT = 800

x = 0.0
y = 0.0

if __name__ == "__main__":
    pyzzle.makeSquare()
    pyzzle.init("basicPuzzleGame", "Basic Puzzle Game", WIDTH, HEIGHT)

def update(): 
    global x
    global y
    global WIDTH

    x += 2.0
    y += 2.0

    if(x > WIDTH): 
        x = 0.0
        y = 0.0
    pyzzle.moveSquare(x, y)

def draw(): 
    pyzzle.drawSquare()

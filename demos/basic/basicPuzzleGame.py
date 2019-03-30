from pyzzle import game
from pyzzle import spriteEngine

WIDTH = 400
HEIGHT = 400

x = 0.0
y = 0.0
speed = 1.0

if __name__ == "__main__":
    spriteEngine.makeSquare()
    game.init("basicPuzzleGame", "Basic Puzzle Game", WIDTH, HEIGHT)

def update(): 
    global x
    global y
    global speed
    global WIDTH

    x += speed
    y += speed
    speed += 0.01

    if(x > WIDTH): 
        x = 0.0
        y = 0.0
    spriteEngine.moveSquare(x, y)

def draw(): 
    spriteEngine.drawSquare()

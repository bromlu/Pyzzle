from pyzzle import game
from pyzzle import sprites

WIDTH = 400
HEIGHT = 400

x = 0.0
y = 0.0

x1 = WIDTH-20
y1 = 0.0
speed = 1.0

if __name__ == "__main__":
    sprites.makeSquare()
    sprites.makeSquare()
    game.init("basicPuzzleGame", "Basic Puzzle Game", WIDTH, HEIGHT)

def update(): 
    global x
    global y
    global x1
    global y1
    global speed
    global WIDTH

    x += speed
    y += speed
    x1 -= speed
    y1 += speed
    speed += 0.01

    if(x > WIDTH): 
        x = 0.0
        y = 0.0

    if(x1 < 0 - 20): 
        x1 = WIDTH-20
        y1 = 0.0
    
    sprites.moveSquare(x, y, 0)
    sprites.moveSquare(x1, y1, 1)

def draw(): 
    sprites.drawSquare(0)
    sprites.drawSquare(1)

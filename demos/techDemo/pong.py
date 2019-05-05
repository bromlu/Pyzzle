from constants import WIDTH, HEIGHT
from pyzzle import game
from pyzzle import input
from pyzzle import sprites
from pyzzle import collision
from pyzzle import shapes

leftPaddle = None
rightPaddle = None
PADDLE_HEIGHT = 24
PADDLE_WIDTH = 4
PADDLE_SCALE = 3
PADDLE_SPEED = 10

if __name__ == "__main__":
    game.init("pong", "Pyzzle Tech Demo", WIDTH, HEIGHT)

class Paddle:
    def __init__(self, x, y):
        self.index = game.createGameObject()
        game.setGameObjectPosition(self.index, x, y)
        sprites.add(self.index, "sprites.png")
        sprites.setFrame(self.index, 8, 11, PADDLE_WIDTH, PADDLE_HEIGHT)
        sprites.setScale(self.index, PADDLE_SCALE, PADDLE_SCALE)

def init():
    global leftPaddle
    global rightPaddle
    leftPaddle = Paddle(100, HEIGHT / 2 - PADDLE_HEIGHT / 2)
    rightPaddle = Paddle(WIDTH - 100 - PADDLE_WIDTH, HEIGHT / 2 - PADDLE_HEIGHT / 2)

def update():
    leftPaddleY = game.getGameObjectPosition(leftPaddle.index)[1]
    rightPaddleY = game.getGameObjectPosition(rightPaddle.index)[1]
    if input.isKeyPressed(18): #S
        if leftPaddleY + PADDLE_HEIGHT * PADDLE_SCALE < HEIGHT:
            game.moveGameObject(leftPaddle.index, 0, PADDLE_SPEED)
    if input.isKeyPressed(22): #W
        if leftPaddleY > 0:
            game.moveGameObject(leftPaddle.index, 0, -PADDLE_SPEED)
    if input.isKeyPressed(74): #Down
        if rightPaddleY + PADDLE_HEIGHT * PADDLE_SCALE < HEIGHT:
            game.moveGameObject(rightPaddle.index, 0, PADDLE_SPEED)
    if input.isKeyPressed(73): #Up
        if rightPaddleY > 0:
            game.moveGameObject(rightPaddle.index, 0, -PADDLE_SPEED)

def drawMiddleLine():
    x = WIDTH / 2 - 2
    for y in range(0, HEIGHT, 100):
        shapes.drawRectangle(int(x), y, 4, 50)

def draw():
    global leftPaddle
    sprites.draw(leftPaddle.index)
    sprites.draw(rightPaddle.index)
    drawMiddleLine()
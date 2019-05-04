from constants import WIDTH, HEIGHT
from pyzzle import game
from pyzzle import input
from pyzzle import sprites
from pyzzle import collision

leftPaddle = None
rightPaddle = None
PADDLE_HEIGHT = 24
PADDLE_WIDTH = 4
PADDLE_SCALE = 3

if __name__ == "__main__":
    game.init("pong", "Pyzzle Tech Demo", WIDTH, HEIGHT)

class Paddle:
    def __init__(self):
        self.index = game.createGameObject()
        game.setGameObjectPosition(self.index, WIDTH/2, HEIGHT/2)
        sprites.add(self.index, "sprites.png")
        sprites.setFrame(self.index, 8, 11, PADDLE_WIDTH, PADDLE_HEIGHT)
        sprites.setScale(self.index, PADDLE_SCALE, PADDLE_SCALE)

def init():
    global leftPaddle
    global rightPaddle
    leftPaddle = Paddle()
    rightPaddle = Paddle()

def update():
    leftPaddleY = game.getGameObjectPosition(leftPaddle.index)[1]
    rightPaddleY = game.getGameObjectPosition(rightPaddle.index)[1]
    if input.isKeyPressed(18): #S
        if leftPaddleY + PADDLE_HEIGHT * PADDLE_SCALE < HEIGHT:
            game.moveGameObject(leftPaddle.index, 0, 5)
    if input.isKeyPressed(22): #W
        if leftPaddleY > 0:
            game.moveGameObject(leftPaddle.index, 0, -5)
    if input.isKeyPressed(74): #Down
        if rightPaddleY + PADDLE_HEIGHT * PADDLE_SCALE < HEIGHT:
            game.moveGameObject(rightPaddle.index, 0, 5)
    if input.isKeyPressed(73): #Up
        if rightPaddleY > 0:
            game.moveGameObject(rightPaddle.index, 0, -5)

def draw():
    global leftPaddle
    sprites.draw(leftPaddle.index)
    sprites.draw(rightPaddle.index)
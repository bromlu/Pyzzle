from constants import WIDTH, HEIGHT
from pyzzle import game
from pyzzle import input
from pyzzle import sprites
from pyzzle import collision
from pyzzle import shapes
from pyzzle import text

leftPaddle = None
rightPaddle = None
ball = None
leftScore = 0
rightScore = 0
PADDLE_HEIGHT = 24
PADDLE_WIDTH = 4
PADDLE_SCALE = 3
PADDLE_SPEED = 10
BALL_RADIUS = 6
BALL_SCALE = 3
BALL_SPEED = 10

if __name__ == "__main__":
    text.loadFont("trench100free.otf")
    game.init("pong", "Pyzzle Tech Demo", WIDTH, HEIGHT)

class Paddle:
    def __init__(self, x, y):
        self.index = game.createGameObject()
        game.setGameObjectPosition(self.index, x, y)
        sprites.add(self.index, "sprites.png")
        sprites.setFrame(self.index, 8, 11, PADDLE_WIDTH, PADDLE_HEIGHT)
        sprites.setScale(self.index, PADDLE_SCALE, PADDLE_SCALE)

class Ball:
    def __init__(self):
        self.index = game.createGameObject()
        self.vx = BALL_SPEED
        self.vy = 0
        game.setGameObjectPosition(self.index, WIDTH / 2 - BALL_RADIUS * BALL_SCALE / 2, HEIGHT / 2 - BALL_RADIUS * BALL_SCALE / 2)
        sprites.add(self.index, "sprites.png")
        sprites.setFrame(self.index, 27, 21, BALL_RADIUS, BALL_RADIUS)
        sprites.setScale(self.index, BALL_SCALE, BALL_SCALE)


def init():
    global leftPaddle
    global rightPaddle
    global ball
    ball = Ball()
    leftPaddle = Paddle(100, HEIGHT / 2 - PADDLE_HEIGHT / 2)
    rightPaddle = Paddle(WIDTH - 100 - PADDLE_WIDTH, HEIGHT / 2 - PADDLE_HEIGHT / 2)

def update():
    global ball
    global leftPaddle
    global rightPaddle
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
    game.moveGameObject(ball.index, ball.vx, ball.vy)

def drawMiddleLine():
    shapes.setOutline(0)
    shapes.setFill()
    x = WIDTH / 2 - 2
    for y in range(0, HEIGHT, 100):
        shapes.drawRectangle(int(x), y, 4, 50)

def draw():
    global rightPaddle
    global leftPaddle
    global leftScore
    global rightScore
    global ball
    sprites.draw(leftPaddle.index)
    sprites.draw(rightPaddle.index)
    sprites.draw(ball.index)
    text.draw(str(leftScore), 100, 100, 100)
    text.draw(str(rightScore), WIDTH - 100, 100, 100)
    drawMiddleLine()
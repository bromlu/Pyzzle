import math
import random
from constants import WIDTH, HEIGHT
from pyzzle import game
from pyzzle import input
from pyzzle import sprites
from pyzzle import collision
from pyzzle import shapes
from pyzzle import text

winMessage = ""
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
        collision.addCollisionRect(self.index, 0, 0, PADDLE_WIDTH, PADDLE_HEIGHT, PADDLE_SCALE)
        sprites.add(self.index, "sprites.png")
        sprites.setFrame(self.index, 8, 11, PADDLE_WIDTH, PADDLE_HEIGHT)
        sprites.setScale(self.index, PADDLE_SCALE, PADDLE_SCALE)

def resetBall():
    global ball
    angle = random.choice([random.randint(-45, 45), random.randint(135, 225)]) * math.pi / 180.0;
    ball.vx = BALL_SPEED * math.cos(angle)
    ball.vy = BALL_SPEED * -math.sin(angle)
    game.setGameObjectPosition(ball.index, WIDTH / 2 - BALL_RADIUS * BALL_SCALE / 2, HEIGHT / 2 - BALL_RADIUS * BALL_SCALE / 2)

class Ball:
    def __init__(self):
        self.index = game.createGameObject()
        collision.addCollisionRect(self.index, 0, 0, BALL_RADIUS, BALL_RADIUS, BALL_SCALE)
        sprites.add(self.index, "sprites.png")
        sprites.setFrame(self.index, 27, 21, BALL_RADIUS, BALL_RADIUS)
        sprites.setScale(self.index, BALL_SCALE, BALL_SCALE)

def init():
    global leftPaddle
    global rightPaddle
    global leftScore
    global rightScore
    global ball
    leftScore = 0
    rightScore = 0
    ball = Ball()
    resetBall()
    leftPaddle = Paddle(100, HEIGHT / 2 - PADDLE_HEIGHT / 2)
    rightPaddle = Paddle(WIDTH - 100 - PADDLE_WIDTH, HEIGHT / 2 - PADDLE_HEIGHT / 2)

def bounce(paddleIndex):
    global ball
    paddlePosition = game.getGameObjectPosition(paddleIndex)
    relativeX = paddlePosition[0] - WIDTH/2
    relativeY = paddlePosition[1] - HEIGHT/2
    normalize = math.sqrt(relativeX * relativeX + relativeY * relativeY)
    centerX = (relativeX / normalize) * 50
    centerY = (relativeY / normalize) * 50

    ballPosition = game.getGameObjectPosition(ball.index)
    relativeX = ballPosition[0] - (paddlePosition[0] + centerX)
    relativeY = ballPosition[1] - (paddlePosition[1] + centerY)
    normalize = math.sqrt(relativeX * relativeX + relativeY * relativeY)
    ball.vx = relativeX/normalize * BALL_SPEED
    ball.vy = relativeY/normalize * BALL_SPEED

def update():
    global ball
    global leftPaddle
    global rightPaddle
    global rightScore
    global leftScore
    global winMessage
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
    ballPosition = game.getGameObjectPosition(ball.index)
    if ballPosition[1] + BALL_RADIUS >= HEIGHT or ballPosition[1] <= 0:
        ball.vy = -ball.vy
    if collision.collides(leftPaddle.index, ball.index):
        bounce(leftPaddle.index)
    elif collision.collides(rightPaddle.index, ball.index):
        bounce(rightPaddle.index)

    if ballPosition[0] + BALL_RADIUS >= WIDTH:
        rightScore+=1
        if rightScore == 10:
            winMessage = "Right Player WINS!"
            game.switchState("pong", "", "gameOverUpdate", "gameOverDraw")
        else:
            resetBall()
    elif ballPosition[0] <= 0:
        leftScore+=1
        if leftScore == 10:
            winMessage = "Left Player WINS!"
            game.switchState("pong", "", "gameOverUpdate", "gameOverDraw")
        else:
            resetBall()

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

def gameOverUpdate():
    if input.isKeyPressed(36): #escape
        game.switchState("menu", "initPlay", "update", "draw")
    elif input.isKeyPressed(57): #space
        game.switchState("pong", "init", "update", "draw")

def gameOverDraw():
    global winMessage
    text.draw(winMessage, WIDTH/2, HEIGHT/2 - 100, 64.0)
    text.draw("Hit [esc] to go back to menu or [space] to play again.", WIDTH/2, HEIGHT/2 + 100, 48.0)
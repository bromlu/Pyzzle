import math
from random import randint

from pyzzle import game
from pyzzle import input
from pyzzle import sprites
from pyzzle import shapes
from pyzzle import text



#WIDTH = 800
#HEIGHT = 800
BOARDWIDTH = 50
BOARDHEIGHT = 40
TILESIZE = 16
HEADERHEIGHT = 64
PADDING = 6
PLAYWIDTH = BOARDWIDTH * TILESIZE
PLAYHEIGHT = BOARDHEIGHT * TILESIZE
PLAYOFFSET = PADDING * 2 + HEADERHEIGHT
WIDTH = PLAYWIDTH + PADDING * 2
HEIGHT = PLAYHEIGHT + PADDING * 3 + HEADERHEIGHT
MINECOUNT = 5

board = []
thing = 0

tile_blank = game.createGameObject()
sprites.add(tile_blank, "assets/tile_blank.png")

if __name__ == "__main__":
	# text.loadFont("trench100free.otf")
	game.init("mines", "Mine Sweeper", WIDTH, HEIGHT)



def print_board():
	for row in board:
		print(row)



# BOARD INIT FUNCTIONS-------------------------------------------------------------------------->
def randtile():
	r = randint(0, BOARDWIDTH * BOARDHEIGHT - 1)
	return r % BOARDWIDTH, math.floor(r / BOARDWIDTH)

def adj_increment(x, y):
	if(x >= 0 and x < BOARDWIDTH and y >= 0 and y < BOARDHEIGHT and board[y][x][0] != -1):
		board[y][x][0] += 1

def place_mines():
	for i in range(MINECOUNT):
		x, y = randtile()
		while(board[y][x][0] == -1):
			x, y = randtile()

		board[y][x][0] = -1
		adj_increment(x, y - 1)
		adj_increment(x + 1, y - 1)
		adj_increment(x + 1, y)
		adj_increment(x + 1, y + 1)
		adj_increment(x, y + 1)
		adj_increment(x - 1, y + 1)
		adj_increment(x - 1, y)
		adj_increment(x - 1, y - 1)

def reset_board():
	global board
	board = []
	for y in range(BOARDHEIGHT):
		board.append([])
		for x in range(BOARDWIDTH):
			board[y].append([0, False])

	place_mines()



# DRAW FUNCTIONS-------------------------------------------------------------------------------->
def draw_outline():
	shapes.setOutline(0)
	shapes.setFill()
	shapes.setColor(20, 20, 19)
	shapes.drawRectangle(0, 0, WIDTH, HEIGHT)
	shapes.setOutline(PADDING)
	shapes.setColor(102, 100, 98)
	shapes.drawRectangle(0, 0, WIDTH, PLAYOFFSET)
	shapes.setOutline(PADDING)
	shapes.setColor(102, 100, 98)
	shapes.drawRectangle(0, HEADERHEIGHT + PADDING, PLAYWIDTH + PADDING * 2, PLAYHEIGHT + PADDING * 2)

def draw_board():
	global thing
	for y in range(BOARDHEIGHT):
		for x in range(BOARDWIDTH):
			game.setGameObjectPosition(tile_blank, PADDING * 2 + x * TILESIZE + 2, PLAYOFFSET + y * TILESIZE + PADDING + 2)
			sprites.draw(tile_blank)



# ENGINE FUNCTIONS------------------------------------------------------------------------------>
def init():
	reset_board()
	print_board()

def update():
	return

def draw():
	global thing
	draw_outline()
	draw_board()
	print(thing)
	thing += 1


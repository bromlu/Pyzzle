import math
import time
from random import randint

from pyzzle import game
from pyzzle import input
from pyzzle import sprites
from pyzzle import shapes
from pyzzle import text



#WIDTH = 800
#HEIGHT = 800
SCALE = 2
BOARDWIDTH = 10
BOARDHEIGHT = 10
TILESIZE = 16 * SCALE
HEADERHEIGHT = 64 * SCALE
PADDING = 6 * SCALE
SPRITEERROR = math.floor(TILESIZE / 2)
PLAYWIDTH = BOARDWIDTH * TILESIZE
PLAYHEIGHT = BOARDHEIGHT * TILESIZE
PLAYOFFSET = PADDING * 2 + HEADERHEIGHT
WIDTH = PLAYWIDTH + PADDING * 2
HEIGHT = PLAYHEIGHT + PADDING * 3 + HEADERHEIGHT
MINECOUNT = math.floor(BOARDWIDTH * BOARDHEIGHT * .15) #30
CURSOROUTLINE = 2 * SCALE

board = []
cursorx = math.floor(BOARDWIDTH / 2);
cursory = math.floor(BOARDHEIGHT / 2);
cursor_paused = False
cursor_pause = 0
game_state = 0
action_paused = False
clear_buffer = []
left = MINECOUNT
first = True
base_time = 0
display_time = "0"

tile_blank = game.createGameObject()
tile_clear = game.createGameObject()
tile_1 = game.createGameObject()
tile_2 = game.createGameObject()
tile_3 = game.createGameObject()
tile_4 = game.createGameObject()
tile_5 = game.createGameObject()
tile_6 = game.createGameObject()
tile_7 = game.createGameObject()
tile_8 = game.createGameObject()
tile_flag = game.createGameObject()
tile_bomb = game.createGameObject()
tile_boom = game.createGameObject()
tile_wrong = game.createGameObject()

sprites.add(tile_blank, "assets/tile_blank.png")
sprites.add(tile_clear, "assets/tile_clear.png")
sprites.add(tile_1, "assets/tile_1.png")
sprites.add(tile_2, "assets/tile_2.png")
sprites.add(tile_3, "assets/tile_3.png")
sprites.add(tile_4, "assets/tile_4.png")
sprites.add(tile_5, "assets/tile_5.png")
sprites.add(tile_6, "assets/tile_6.png")
sprites.add(tile_7, "assets/tile_7.png")
sprites.add(tile_8, "assets/tile_8.png")
sprites.add(tile_flag, "assets/tile_flag.png")
sprites.add(tile_bomb, "assets/tile_bomb.png")
sprites.add(tile_boom, "assets/tile_boom.png")
sprites.add(tile_wrong, "assets/tile_wrong.png")

sprites.setScale(tile_blank, SCALE, SCALE)
sprites.setScale(tile_clear, SCALE, SCALE)
sprites.setScale(tile_1, SCALE, SCALE)
sprites.setScale(tile_2, SCALE, SCALE)
sprites.setScale(tile_3, SCALE, SCALE)
sprites.setScale(tile_4, SCALE, SCALE)
sprites.setScale(tile_5, SCALE, SCALE)
sprites.setScale(tile_6, SCALE, SCALE)
sprites.setScale(tile_7, SCALE, SCALE)
sprites.setScale(tile_8, SCALE, SCALE)
sprites.setScale(tile_flag, SCALE, SCALE)
sprites.setScale(tile_bomb, SCALE, SCALE)
sprites.setScale(tile_boom, SCALE, SCALE)
sprites.setScale(tile_wrong, SCALE, SCALE)

if __name__ == "__main__":
	text.loadFont("assets/FSEX300.ttf")
	game.init("mines", "Mine Sweeper", WIDTH, HEIGHT)



# DEBUG FUNCTIONS------------------------------------------------------------------------------->
def print_board():
	for row in board:
		print(row)



# HELPER FUNCTIONS------------------------------------------------------------------------------>
def clamp(n, mi, ma):
	if n > ma:
		n = ma
	elif n < mi:
		n = mi
	
	return n

def check_keys(li):
	for key in li:
		if input.isKeyPressed(key):
			return True
	return False

def tile_exists(x, y):
	return x >= 0 and x < BOARDWIDTH and y >= 0 and y < BOARDHEIGHT

def move_and_draw(x, y, obj):
	game.setGameObjectPosition(obj, PADDING + x * TILESIZE + SPRITEERROR, PLAYOFFSET + y * TILESIZE + SPRITEERROR)
	sprites.draw(obj)



# BOARD INIT FUNCTIONS-------------------------------------------------------------------------->
def randtile():
	r = randint(0, BOARDWIDTH * BOARDHEIGHT - 1)
	return r % BOARDWIDTH, math.floor(r / BOARDWIDTH)

def adj_increment(x, y):
	if tile_exists(x, y) and board[y][x][0] != -1:
		board[y][x][0] += 1

def place_mine(avoidx, avoidy):
	x, y = randtile()
	while board[y][x][0] == -1 or board[y][x][0] == 8 or (x >= avoidx - 1 and x <= avoidx + 1 and y >= avoidy - 1 and y <= avoidy + 1):
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

def place_mines(avoidx, avoidy):
	for i in range(MINECOUNT):
		place_mine(avoidx, avoidy)

def reset_board():
	global board
	board = []
	for y in range(BOARDHEIGHT):
		board.append([])
		for x in range(BOARDWIDTH):
			board[y].append([0, 0])

def clear_board():
	global board, left
	left = 0

	for y in range(BOARDHEIGHT):
		for x in range(BOARDWIDTH):
			if board[y][x][0] == -1:
				board[y][x][1] = 1
			if board[y][x][1] == 0:
				board[y][x][1] = 2
	
def reveal_mines():
	global board

	for y in range(BOARDHEIGHT):
		for x in range(BOARDWIDTH):
			if board[y][x][0] == -1 and board[y][x][1] == 0:
				board[y][x][1] = 2
			elif board[y][x][0] != -1 and board[y][x][1] == 1:
				board[y][x][1] = -1



# UPDATE FUNCTIONS------------------------------------------------------------------------------>
def lose():
	global game_state
	game_state = -1
	reveal_mines()
	print("You Lost!")

def win():
	global game_state
	game_state = 1
	clear_board()
	print("You Won!")

def check_mines():
	for y in range(BOARDHEIGHT):
		for x in range(BOARDWIDTH):
			if (board[y][x][0] == -1 and board[y][x][1] != 1) or (board[y][x][0] != -1 and board[y][x][1] == 1):
				return False
	return True
	
def check_clears():
	for y in range(BOARDHEIGHT):
		for x in range(BOARDWIDTH):
			if board[y][x][0] != -1 and board[y][x][1] != 2:
				return False
	return True

def flag_tile():
	global cursorx, cursory, board, left

	if board[cursory][cursorx][1] == 0:
		board[cursory][cursorx][1] = 1
		left -= 1
	elif board[cursory][cursorx][1] == 1:
		board[cursory][cursorx][1] = 0
		left += 1

	if left == 0 and check_mines():
		win()

def clear_tile(x, y, base = False):
	global board

	if tile_exists(x, y) and base and board[y][x][0] == -1 and board[y][x][1] == 0:
		board[y][x][0] = -2
		lose()

	if tile_exists(x, y) and board[y][x][1] == 0 and ((base) or (not base and board[y][x][0] != -1)):
		board[y][x][1] = 2

		if board[y][x][0] == 0:
			clear_buffer.append([x, y - 1])
			clear_buffer.append([x + 1, y - 1])
			clear_buffer.append([x + 1, y])
			clear_buffer.append([x + 1, y + 1])
			clear_buffer.append([x, y + 1])
			clear_buffer.append([x - 1, y + 1])
			clear_buffer.append([x - 1, y])
			clear_buffer.append([x - 1, y - 1])

def handle_move():
	global cursorx, cursory, cursor_paused, cursor_pause
	cursor_move = False

	if cursor_paused:
		cursor_pause -= 1
		if cursor_pause <= 0:
			cursor_paused = False
	
	if check_keys([22, 0, 18, 3, 71, 72, 73, 74]):
		if not cursor_paused:
			cursor_paused = True
			cursor_move = True
			cursor_pause = 20
		elif cursor_pause == 1:
			cursor_paused = True
			cursor_move = True
			cursor_pause = 4
	else:
		cursor_paused = False
		cursor_pause = 0
	
	if cursor_move:
		if input.isKeyPressed(22) or input.isKeyPressed(73):
			cursory -= 1
		if input.isKeyPressed(0) or input.isKeyPressed(71):
			cursorx -= 1
		if input.isKeyPressed(18) or input.isKeyPressed(74):
			cursory += 1
		if input.isKeyPressed(3) or input.isKeyPressed(72):
			cursorx += 1
	
		cursorx = clamp(cursorx, 0, BOARDWIDTH - 1)
		cursory = clamp(cursory, -1, BOARDHEIGHT - 1)

def handle_action():
	global action_paused, first, base_time, display_time, left, game_state
	action = False

	if check_keys([23, 25]):
		if not action_paused:
			action = True
			action_paused = True
	else:
		action_paused = False

	if action and game_state == 0:
		if input.isKeyPressed(23):
			flag_tile()
		elif input.isKeyPressed(25):
			if first:
				place_mines(cursorx, cursory)
				first = False
				base_time = time.time()

			clear_tile(cursorx, cursory, True)
			while len(clear_buffer) > 0:
				n = clear_buffer.pop()
				clear_tile(n[0], n[1])

		if check_clears():
			win()
	if action and cursory == -1:
		reset_board()
		first = True
		display_time = "0"
		left = MINECOUNT
		game_state = 0

def update_time():
	global display_time
	if not first and game_state == 0:
		display_time = str(math.floor(time.time() - base_time))



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
	for y in range(BOARDHEIGHT):
		for x in range(BOARDWIDTH):
			if board[y][x][1] == 1:
				move_and_draw(x, y, tile_flag)
			elif board[y][x][1] == 2:
				if board[y][x][0] == -2:
					move_and_draw(x, y, tile_boom)
				if board[y][x][0] == -1:
					move_and_draw(x, y, tile_bomb)
				if board[y][x][0] == 0:
					move_and_draw(x, y, tile_clear)
				if board[y][x][0] == 1:
					move_and_draw(x, y, tile_1)
				if board[y][x][0] == 2:
					move_and_draw(x, y, tile_2)
				if board[y][x][0] == 3:
					move_and_draw(x, y, tile_3)
				if board[y][x][0] == 4:
					move_and_draw(x, y, tile_4)
				if board[y][x][0] == 5:
					move_and_draw(x, y, tile_5)
				if board[y][x][0] == 6:
					move_and_draw(x, y, tile_6)
				if board[y][x][0] == 7:
					move_and_draw(x, y, tile_7)
				if board[y][x][0] == 8:
					move_and_draw(x, y, tile_8)
			elif board[y][x][1] == -1:
				move_and_draw(x, y, tile_wrong)
			else:
				move_and_draw(x, y, tile_blank)

def draw_header():
	str_left = str(left)
	text.draw(str_left, PADDING + ((len(str_left) * 28 / 2) + 14) * SCALE, PADDING + 29 * SCALE, 64 * SCALE, 248, 246, 242)
	text.draw(display_time, WIDTH - (PADDING + math.floor(len(display_time) * 28 / 2) + 14) * SCALE, PADDING + 29 * SCALE, 64 * SCALE, 248, 246, 242)
	
def draw_cursor():
	global cursorx, cursory
	if cursory != -1:
		shapes.setOutline(CURSOROUTLINE)
		shapes.setColor(255, 167, 36)
		shapes.drawRectangle(PADDING + cursorx * TILESIZE - CURSOROUTLINE, PLAYOFFSET + cursory * TILESIZE - CURSOROUTLINE, TILESIZE + CURSOROUTLINE * 2, TILESIZE + CURSOROUTLINE * 2)
	else:
		shapes.setOutline(CURSOROUTLINE)
		shapes.setColor(255, 167, 36)
		shapes.drawRectangle(int((WIDTH - HEADERHEIGHT) / 2), PADDING, HEADERHEIGHT, HEADERHEIGHT)



# ENGINE FUNCTIONS------------------------------------------------------------------------------>
def init():
	reset_board()
	#print_board()

def update():
	handle_move()
	handle_action()
	update_time()

def draw():
	draw_outline()
	draw_board()
	draw_header()
	draw_cursor()


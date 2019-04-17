from pyzzle import game
from pyzzle import sprites
from pyzzle import animations
from pyzzle import input
from pyzzle import collision

WIDTH = 800
HEIGHT = 800

gameObjects = { }

if __name__ == "__main__":
	game.init("collision", "Collision Test", WIDTH, HEIGHT)

def init():
	global gameObjects
	gameObjects["obj1"] = game.createGameObject()
	sprites.addSprite(gameObjects["obj1"], "MainCharacter.png")
	sprites.setStartFrame(gameObjects["obj1"], 0, 64, 24, 32)
	game.setGameObjectPosition(gameObjects["obj1"], WIDTH/2, HEIGHT/2)
	collision.addCollisionRect(gameObjects["obj1"], 0, 6 * 5, 24 * 5, 10 * 5)
	collision.addCollisionRect(gameObjects["obj1"], 4 * 5, 16 * 5, 16 * 5, 16 * 5)
	
	gameObjects["obj2"] = game.createGameObject()
	sprites.addSprite(gameObjects["obj2"], "MainCharacter.png")
	sprites.setStartFrame(gameObjects["obj2"], 0, 64, 24, 32)
	game.setGameObjectPosition(gameObjects["obj2"], WIDTH/4, HEIGHT/4)
	collision.addCollisionRect(gameObjects["obj2"], 0, 6, 24, 10, 5)
	collision.addCollisionRect(gameObjects["obj2"], 4, 16, 16, 16, 5)

def update(): 
	global gameObjects
	if input.isKeyPressed(22): #W
		sprites.setStartFrame(gameObjects["obj1"], 0, 0, 24, 32)
		game.moveGameObject(gameObjects["obj1"], 0, -10)
		animations.play(gameObjects["obj1"])
	if input.isKeyPressed(0): #A
		sprites.setStartFrame(gameObjects["obj1"], 0, 96, 24, 32)
		game.moveGameObject(gameObjects["obj1"], -10, 0)
		animations.play(gameObjects["obj1"])
	if input.isKeyPressed(3): #D
		sprites.setStartFrame(gameObjects["obj1"], 0, 32, 24, 32)
		game.moveGameObject(gameObjects["obj1"], 10, 0)
		animations.play(gameObjects["obj1"])
	if input.isKeyPressed(18): #S
		sprites.setStartFrame(gameObjects["obj1"], 0, 64, 24, 32)
		game.moveGameObject(gameObjects["obj1"], 0, 10)
		animations.play(gameObjects["obj1"])
	
	if input.isKeyPressed(8):
		sprites.setStartFrame(gameObjects["obj2"], 0, 0, 24, 32)
		game.moveGameObject(gameObjects["obj2"], 0, -10)
		animations.play(gameObjects["obj2"])
	if input.isKeyPressed(9):
		sprites.setStartFrame(gameObjects["obj2"], 0, 96, 24, 32)
		game.moveGameObject(gameObjects["obj2"], -10, 0)
		animations.play(gameObjects["obj2"])
	if input.isKeyPressed(11):
		sprites.setStartFrame(gameObjects["obj2"], 0, 32, 24, 32)
		game.moveGameObject(gameObjects["obj2"], 10, 0)
		animations.play(gameObjects["obj2"])
	if input.isKeyPressed(10):
		sprites.setStartFrame(gameObjects["obj2"], 0, 64, 24, 32)
		game.moveGameObject(gameObjects["obj2"], 0, 10)
		animations.play(gameObjects["obj2"])

	print(collision.collides(gameObjects["obj1"], gameObjects["obj2"]))
	pass

def draw(): 
	global gameObjects
	sprites.draw(gameObjects["obj1"])
	sprites.draw(gameObjects["obj2"])
	collision.drawCollisionObjects(gameObjects["obj1"]);
	collision.drawCollisionObjects(gameObjects["obj2"]);

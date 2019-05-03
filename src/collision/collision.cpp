#include <Python.h>
#include <SFML/Graphics.hpp>
#include "./../game.hpp"
#include "./../gameObject/GameObject.hpp"
#include <iostream>
using namespace std;

static PyObject *
collision_addCollisionRect(PyObject *self, PyObject *args) {
	long index;
	int left;
	int top;
	int width;
	int height;
	int scale = 0;

	if(!PyArg_ParseTuple(args, "liiii|i", &index, &left, &top, &width, &height, &scale))
		return NULL;

	if(scale == 0) scale = 1;

	GameObject* gameObject = game_getGameObject(index);
	gameObject->addRect(left * scale, top * scale, width * scale, height * scale);

	Py_RETURN_NONE;
}

static PyObject *
collision_drawCollisionObjects(PyObject *self, PyObject * args) {
	long index;

	if(!PyArg_ParseTuple(args, "l", &index))
		return NULL;

	GameObject* gameObject = game_getGameObject(index);
	gameObject->drawCollisionObjects(game_getWindow());

	Py_RETURN_NONE;
}

static PyObject *
collision_contains(PyObject *self, PyObject *args) {
	long index;
	float x;
	float y;

	if(!PyArg_ParseTuple(args, "lff", &index, &x, &y))
		return NULL;

	GameObject* gameObject = game_getGameObject(index);

	if(gameObject->contains(sf::Vector2f(x, y)))
		Py_RETURN_TRUE;

	Py_RETURN_FALSE;
}

static PyObject *
collision_collides(PyObject *self, PyObject *args) {
	long index1;
	long index2;

	if(!PyArg_ParseTuple(args, "ll", &index1, &index2))
		return NULL;

	GameObject* gameObject1 = game_getGameObject(index1);
	GameObject* gameObject2 = game_getGameObject(index2);

	if(gameObject1->collides(gameObject2))
		Py_RETURN_TRUE;

	Py_RETURN_FALSE;
}

static PyObject *
collision_intersects(PyObject *self, PyObject *args) {
	long index;
	float x1;
	float y1;
	float x2;
	float y2;

	if(!PyArg_ParseTuple(args, "lffff", &index, &x1, &y1, &x2, &y2))
		return NULL;

	GameObject* gameObject = game_getGameObject(index);

	if(gameObject->intersects(x1, y1, x2, y2))
		Py_RETURN_TRUE;

	Py_RETURN_FALSE;
}

static PyMethodDef collisionMethods[] =  {
	{"addCollisionRect", collision_addCollisionRect, METH_VARARGS,
     "Initializes a collision rectangle to a game object."},
	
	{"drawCollisionObjects", collision_drawCollisionObjects, METH_VARARGS,
     "Draws the collisions objects of a game object."},
	
	{"contains", collision_contains, METH_VARARGS,
     "Checks if a rect contains a point."},
	
	{"collides", collision_collides, METH_VARARGS,
     "Checks if one game object collides with another."},
	
	{"intersects", collision_intersects, METH_VARARGS,
     "Checks if a line intersects a game object."},

	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef collisionModule = {
	PyModuleDef_HEAD_INIT,
	"pyzzle.collision",
	NULL,
	-1,
	collisionMethods
};

PyMODINIT_FUNC PyInit_collision(void) {
	PyObject *module;

	module = PyModule_Create(&collisionModule);
	if(module == NULL)
		return NULL;
	if(import_game() < 0)
		return NULL;
	return module;
}

#include <Python.h>
#include <SFML/Graphics.hpp>
#include "./../game.hpp"
#include <iostream>
using namespace std;

static PyObject *
spriteEngine_makeSquare(PyObject *self, PyObject *args)
{
    long index = game_addRectangle();
    sf::RectangleShape* rect = game_getRectangle(index);
    rect->setSize(sf::Vector2f(20, 20));
    rect->setPosition(20, 20);
    rect->setFillColor(sf::Color::Red);
    return PyLong_FromLong(index);
}

static PyObject * spriteEngine_moveSquare(PyObject *self, PyObject *args)
{
    float x;
    float y;
    long index;

    if (!PyArg_ParseTuple(args, "ffl", &x, &y, &index))
        return NULL;

    game_getRectangle(index)->setPosition(x, y);
    Py_RETURN_NONE;
}

static PyObject * spriteEngine_drawSquare(PyObject *self, PyObject *args)
{
    long index;

    if (!PyArg_ParseTuple(args, "l", &index))
        return NULL;

    game_getWindow()->draw(*game_getRectangle(index));
    Py_RETURN_NONE;
}

static PyMethodDef spriteEngineMethods[] = {

    {"makeSquare",  spriteEngine_makeSquare, METH_VARARGS,
     "Initializes a square in the SFML window."},

    {"moveSquare",  spriteEngine_moveSquare, METH_VARARGS,
     "Moves a square in the SFML window."},

    {"drawSquare",  spriteEngine_drawSquare, METH_VARARGS,
     "Draws a square in the SFML window."},

    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef spriteEngineModule = {
    PyModuleDef_HEAD_INIT,
    "pyzzle.spriteEngine",
    NULL,
    -1,
    spriteEngineMethods
};

PyMODINIT_FUNC PyInit_spriteEngine(void)
{
    PyObject *module;

    module = PyModule_Create(&spriteEngineModule);
    if (module == NULL)
        return NULL;
    if (import_game() < 0)
        return NULL;
    return module;
}
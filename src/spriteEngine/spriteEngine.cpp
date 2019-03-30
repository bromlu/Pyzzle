#include <Python.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "./../game.hpp"
using namespace std;

sf::RectangleShape rectangles[1];

static PyObject *
spriteEngine_makeSquare(PyObject *self, PyObject *args)
{
    rectangles[0].setSize(sf::Vector2f(20, 20));
    rectangles[0].setPosition(20, 20);
    rectangles[0].setFillColor(sf::Color::Red);
    Py_RETURN_NONE;
}

static PyObject *
spriteEngine_moveSquare(PyObject *self, PyObject *args)
{
    float x;
    float y;

    if (!PyArg_ParseTuple(args, "ff", &x, &y))
        return NULL;

    rectangles[0].setPosition(x, y);
    Py_RETURN_NONE;
}

static PyObject *
spriteEngine_drawSquare(PyObject *self, PyObject *args)
{
    game_getWindow()->draw(rectangles[0]);
    Py_RETURN_NONE;
}

static PyMethodDef spriteEngineMethods[] = {

    {"makeSquare",  spriteEngine_makeSquare, METH_VARARGS,
     "Initializes a square in the SFML window."},

    {"moveSquare",  spriteEngine_moveSquare, METH_VARARGS,
     "Moves a square in the SFML window."},

    {"drawSquare",  spriteEngine_drawSquare, METH_VARARGS,
     "Draws a square in the SFML window."},

    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef spriteEngineModule = {
    PyModuleDef_HEAD_INIT,
    "pyzzle.spriteEngine",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    spriteEngineMethods
};

PyMODINIT_FUNC
PyInit_spriteEngine(void)
{
    PyObject *module;

    module = PyModule_Create(&spriteEngineModule);
    if (module == NULL)
        return NULL;
    if (import_game() < 0)
        return NULL;
    return module;
}
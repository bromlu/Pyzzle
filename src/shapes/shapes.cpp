#include <Python.h>
#include <SFML/Graphics.hpp>
#include "./../game.hpp"
#include "./../gameObject/GameObject.hpp"
#include <iostream>
using namespace std;


// all:

// draw_line
// text

bool filled = false;
int outline = 10;
sf::Color color = sf::Color(255,255,255,255);


static PyObject * shapes_setColor(PyObject *self, PyObject *args)
{
    int r;
    int g;
    int b;
    int a = 255;

    if (!PyArg_ParseTuple(args, "iii|i", &r, &g, &b, &a))
        return NULL;

    color = sf::Color(r,g,b,a);
    Py_RETURN_NONE;
}

static PyObject * shapes_fill(PyObject *self, PyObject *args)
{
    filled = true;
    Py_RETURN_NONE;
}

// weight
static PyObject * shapes_outline(PyObject *self, PyObject *args)
{
    int weight = 10;

    if (!PyArg_ParseTuple(args, "|i", &weight))
        return NULL;

    outline = weight;
    filled = false;
    Py_RETURN_NONE;
}

// x, y, radius
static PyObject * shapes_drawCircle(PyObject *self, PyObject *args)
{
    int x;
    int y;
    int radius;

    if (!PyArg_ParseTuple(args, "iii", &x, &y, &radius))
        return NULL;

    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Transparent);
    if (filled) {
        shape.setFillColor(color);
    }
    shape.setOutlineThickness(-outline);
    shape.setOutlineColor(color);
    shape.setOrigin(radius, radius);
    shape.setPosition(x, y);

    game_getWindow()->draw(shape);
    Py_RETURN_NONE;
}

// x, y, radius, n
static PyObject * shapes_drawPolygon(PyObject *self, PyObject *args)
{
    int x;
    int y;
    int radius;
    int n;

    if (!PyArg_ParseTuple(args, "iiii", &x, &y, &radius, &n))
        return NULL;

    sf::CircleShape shape(radius, n);
    shape.setFillColor(sf::Color::Transparent);
    if (filled) {
        shape.setFillColor(color);
    }
    shape.setOutlineThickness(-outline);
    shape.setOutlineColor(color);
    shape.setOrigin(radius, radius);
    shape.setPosition(x, y);

    game_getWindow()->draw(shape);
    Py_RETURN_NONE;
}

// x, y, w, h
static PyObject * shapes_drawRectangle(PyObject *self, PyObject *args)
{
    int x;
    int y;
    int w;
    int h;

    if (!PyArg_ParseTuple(args, "iiii", &x, &y, &w, &h))
        return NULL;

    sf::RectangleShape shape(sf::Vector2f(w, h));
    shape.setFillColor(sf::Color::Transparent);
    if (filled) {
        shape.setFillColor(color);
    }
    shape.setOutlineThickness(-outline);
    shape.setOutlineColor(color);
    shape.setPosition(x, y);

    game_getWindow()->draw(shape);
    Py_RETURN_NONE;
}


static PyMethodDef shapesMethods[] = {

    {"drawCircle",  shapes_drawCircle, METH_VARARGS,
     "Draws a circle in the SFML window."},

    {"drawRectangle",  shapes_drawRectangle, METH_VARARGS,
     "Draws a rectangle in the SFML window."},

    {"drawPolygon",  shapes_drawPolygon, METH_VARARGS,
     "Draws any regular polygon in the SFML window."},

    {"setFill",  shapes_fill, METH_VARARGS,
     "All shapes will be drawn filled."},

    {"setOutline",  shapes_outline, METH_VARARGS,
     "All shapes will be drawn with an outline. Default is 10 unless specified, negative draws outside."},

    {"setColor",  shapes_setColor, METH_VARARGS,
     "All shapes will be drawn with an specified color."},

    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef shapesModule = {
    PyModuleDef_HEAD_INIT,
    "pyzzle.shapes",
    NULL,
    -1,
    shapesMethods
};

PyMODINIT_FUNC PyInit_shapes(void)
{
    PyObject *module;

    module = PyModule_Create(&shapesModule);
    if (module == NULL)
        return NULL;
    if (import_game() < 0)
        return NULL;
    return module;
}
#include <Python.h>
#include <SFML/Graphics.hpp>
#include "./../game.hpp"
#include "./../gameObject/GameObject.hpp"
#include <iostream>
using namespace std;

sf::Font font;

sf::Vector2f center(float x, float y, float size, std::string text) {
    size_t len = text.length();
    float width = len * size;
    return sf::Vector2f(x - (width/4), y - (size/3*2));
}

static PyObject * text_loadFont(PyObject *self, PyObject *args)
{
    const char * fileName;

    if (!PyArg_ParseTuple(args, "s", &fileName))
        return NULL;

    font = sf::Font();
    font.loadFromFile(fileName);

    Py_RETURN_FALSE;
}

static PyObject * text_draw(PyObject *self, PyObject *args)
{
    const char * str;
    float x;
    float y;
    float weight = 30.0;
    int r = 255;
    int g = 255;
    int b = 255;
    int a = 255;


    if (!PyArg_ParseTuple(args, "sff|fiiii", &str, &x, &y, &weight, &r, &g, &b, &a))
        return NULL;

    sf::Text text(str, font, weight);
    text.setColor(sf::Color(r, g, b, a));
    text.setPosition(center(x, y, weight, str));
    game_getWindow()->draw(text);

    Py_RETURN_FALSE;
}

static PyMethodDef textMethods[] = {
    {"loadFont",  text_loadFont, METH_VARARGS,
     "Loads the font to be used from a file."},

    {"draw",  text_draw, METH_VARARGS,
     "Draws text to the screen."},

    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef textModule = {
    PyModuleDef_HEAD_INIT,
    "pyzzle.text",
    NULL,
    -1,
    textMethods
};

PyMODINIT_FUNC PyInit_text(void)
{
    PyObject *module;

    module = PyModule_Create(&textModule);
    if (module == NULL)
        return NULL;
    if (import_game() < 0)
        return NULL;
    return module;
}
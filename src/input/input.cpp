#include <Python.h>
#include <SFML/Graphics.hpp>
#include "./../game.hpp"
#include "./../gameObject/GameObject.hpp"
#include <iostream>
using namespace std;

static PyObject * input_isKeyPressed(PyObject *self, PyObject *args)
{
    int key;

    if (!PyArg_ParseTuple(args, "i", &key))
        return NULL;

    if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key))) {
        Py_RETURN_TRUE;
    }

    Py_RETURN_FALSE;
}

static PyMethodDef inputMethods[] = {
    {"isKeyPressed",  input_isKeyPressed, METH_VARARGS,
     "Returns true if a key is pressed."},

    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef inputModule = {
    PyModuleDef_HEAD_INIT,
    "pyzzle.input",
    NULL,
    -1,
    inputMethods
};

PyMODINIT_FUNC PyInit_input(void)
{
    PyObject *module;

    module = PyModule_Create(&inputModule);
    if (module == NULL)
        return NULL;
    if (import_game() < 0)
        return NULL;
    return module;
}
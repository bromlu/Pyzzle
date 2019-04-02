#include <Python.h>
#include <SFML/Graphics.hpp>
#include "./../game.hpp"
#include "./../gameObject/GameObject.hpp"
#include <iostream>
using namespace std;

static PyObject *
sprites_addSprite(PyObject *self, PyObject *args)
{
    long index;
    const char * fileName;

    if (!PyArg_ParseTuple(args, "ls", &index, &fileName))
        return NULL;

    GameObject* gameObject = game_getGameObject(index);
    gameObject->addSprite(fileName);

    Py_RETURN_NONE;
}

static PyObject * sprites_draw(PyObject *self, PyObject *args)
{
    long index;

    if (!PyArg_ParseTuple(args, "l", &index))
        return NULL;

    game_getGameObject(index)->draw(game_getWindow());
    Py_RETURN_NONE;
}

static PyMethodDef spritesMethods[] = {

    {"addSprite",  sprites_addSprite, METH_VARARGS,
     "Initializes a sprite in the SFML window."},

    {"draw",  sprites_draw, METH_VARARGS,
     "Draws a sprite in the SFML window."},

    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef spritesModule = {
    PyModuleDef_HEAD_INIT,
    "pyzzle.sprites",
    NULL,
    -1,
    spritesMethods
};

PyMODINIT_FUNC PyInit_sprites(void)
{
    PyObject *module;

    module = PyModule_Create(&spritesModule);
    if (module == NULL)
        return NULL;
    if (import_game() < 0)
        return NULL;
    return module;
}
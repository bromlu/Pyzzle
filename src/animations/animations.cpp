#include <Python.h>
#include <SFML/Graphics.hpp>
#include "./../game.hpp"
#include "./../gameObject/Animation.hpp"
#include "./../gameObject/GameObject.hpp"
#include <iostream>
using namespace std;

static PyObject * animations_add(PyObject *self, PyObject *args) {
    long index;

    if (!PyArg_ParseTuple(args, "l", &index))
        return NULL;

    GameObject* gameObject = game_getGameObject(index);
    return PyLong_FromLong(gameObject->addAnimation());
}

static PyObject * animations_addFrame(PyObject *self, PyObject *args) {
    long index;
    long animationIndex;
    long x;
    long y;
    long width;
    long height;

    if (!PyArg_ParseTuple(args, "llllll", &index, &animationIndex, &x, &y, &width, &height))
        return NULL;

    GameObject* gameObject = game_getGameObject(index);
    gameObject->addAnimationFrame(animationIndex, x, y, width, height);
    Py_RETURN_NONE;
}

static PyObject * animations_addFrames(PyObject *self, PyObject *args) {
    long index;
    long animationIndex;
    long fromX;
    long fromY;
    long toX;
    long toY;
    long width;
    long height;

    if (!PyArg_ParseTuple(args, "llllllll", 
        &index,  
        &animationIndex, 
        &fromX, 
        &fromY, 
        &toX,
        &toY,
        &width,
        &height))
        return NULL;

    GameObject* gameObject = game_getGameObject(index);
    gameObject->addAnimationFrames(animationIndex, fromX, fromY, toX, toY, width, height);
    Py_RETURN_NONE;
}

static PyObject * animations_stop(PyObject *self, PyObject *args) {
    long gameObjectIndex;
    long animationIndex;

    if (!PyArg_ParseTuple(args, "ll", &gameObjectIndex, &animationIndex))
        return NULL;

    GameObject* gameObject = game_getGameObject(gameObjectIndex);
    Animation* animation = gameObject->getAnimation(animationIndex);
    game_removeActiveAnimation(animation->getGlobalIndex());
    animation->setGlobalIndex(-1);
    Py_RETURN_NONE;
}

static PyObject * animations_play(PyObject *self, PyObject *args)
{
    long gameObjectIndex;
    long animationIndex;

    if (!PyArg_ParseTuple(args, "ll", &gameObjectIndex, &animationIndex))
        return NULL;

    GameObject* gameObject = game_getGameObject(gameObjectIndex);
    Animation* animation = gameObject->getAnimation(animationIndex);
    if (animation->getGlobalIndex() == -1) {
        animation->setGlobalIndex(game_addActiveAnimation(animation));
    }
    Py_RETURN_NONE;
}

static PyMethodDef animationsMethods[] = {
    {"play",  animations_play, METH_VARARGS,
     "Plays a game objects animation."},

    {"stop",  animations_stop, METH_VARARGS,
     "Stops a game objects animation."},

    {"add",  animations_add, METH_VARARGS,
     "Adds a game objects animation."},

    {"addFrame",  animations_addFrame, METH_VARARGS,
     "Adds a frame to an animation."},

    {"addFrames",  animations_addFrames, METH_VARARGS,
     "Adds frames between two points to an animation."},

    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef animationsModule = {
    PyModuleDef_HEAD_INIT,
    "pyzzle.animations",
    NULL,
    -1,
    animationsMethods
};

PyMODINIT_FUNC PyInit_animations(void)
{
    PyObject *module;

    module = PyModule_Create(&animationsModule);
    if (module == NULL)
        return NULL;
    if (import_game() < 0)
        return NULL;
    return module;
}
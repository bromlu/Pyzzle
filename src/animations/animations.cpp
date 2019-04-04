#include <Python.h>
#include <SFML/Graphics.hpp>
#include "./../game.hpp"
#include "./../gameObject/GameObject.hpp"
#include <iostream>
using namespace std;

static PyObject * animations_addAnimation(PyObject *self, PyObject *args) {
    int index;
    int y;

    if (!PyArg_ParseTuple(args, "ii", &index, &y))
        return NULL;

    GameObject* gameObject = game_getGameObject(index);
    return PyLong_FromLong(gameObject->addAnimation(y));
}

static PyObject * animations_stop(PyObject *self, PyObject *args) {
    int gameObjectIndex;
    int animationIndex;

    if (!PyArg_ParseTuple(args, "ii", &gameObjectIndex, &animationIndex))
        return NULL;

    GameObject* gameObject = game_getGameObject(gameObjectIndex);
    sf::Sprite* sprite = gameObject->getSprite(0);
    sf::IntRect oldFrame = sprite->getTextureRect();
    sprite->setTextureRect(sf::IntRect(0, oldFrame.top, oldFrame.width, oldFrame.height));
    Py_RETURN_NONE;
}

static PyObject * animations_play(PyObject *self, PyObject *args)
{
    int gameObjectIndex;
    int animationIndex;

    if (!PyArg_ParseTuple(args, "ii", &gameObjectIndex, &animationIndex))
        return NULL;

    GameObject* gameObject = game_getGameObject(gameObjectIndex);
    if(gameObject->getAnimationElapsedTime() < 0.02){
        Py_RETURN_NONE;
    }
    gameObject->restartAnimationClock();
    sf::Sprite* sprite = gameObject->getSprite(0);
    sf::IntRect oldFrame = sprite->getTextureRect();
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    unsigned int left = oldFrame.left + oldFrame.width;
    int top = gameObject->getAnimation(animationIndex);
    if(left >= textureSize.x) {
        left = 0;
    }
    sprite->setTextureRect(sf::IntRect(left, top, oldFrame.width, oldFrame.height));
    Py_RETURN_NONE;
}

static PyMethodDef animationsMethods[] = {
    {"play",  animations_play, METH_VARARGS,
     "Plays a game objects animation."},

    {"stop",  animations_stop, METH_VARARGS,
     "Plays a game objects animation."},

    {"addAnimation",  animations_addAnimation, METH_VARARGS,
     "Plays a game objects animation."},

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
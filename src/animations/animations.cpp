#include <Python.h>
#include <SFML/Graphics.hpp>
#include "./../game.hpp"
#include "./../gameObject/GameObject.hpp"
#include <iostream>
using namespace std;

static PyObject * animations_play(PyObject *self, PyObject *args)
{
    long index;

    if (!PyArg_ParseTuple(args, "l", &index))
        return NULL;

    GameObject* gameObject = game_getGameObject(index);
    if(gameObject->getAnimationElapsedTime() < 0.02){
        Py_RETURN_NONE;
    }
    gameObject->restartAnimationClock();
    sf::Sprite* sprite = game_getGameObject(index)->getSprite(0);
    sf::IntRect oldFrame = sprite->getTextureRect();
    sf::Vector2u textureSize = sprite->getTexture()->getSize();
    unsigned int left = oldFrame.left + oldFrame.width;
    if(left >= textureSize.x) {
        left = 0;
    }
    sprite->setTextureRect(sf::IntRect(left, oldFrame.top, oldFrame.width, oldFrame.height));
    Py_RETURN_NONE;
}

static PyMethodDef animationsMethods[] = {
    {"play",  animations_play, METH_VARARGS,
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
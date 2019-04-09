#include <Python.h>
#include <SFML/Graphics.hpp>
#include "./../game.hpp"
#include "./../gameObject/Animation.hpp"
#include "./../gameObject/GameObject.hpp"
#include <iostream>
using namespace std;

static PyObject * animations_add(PyObject *self, PyObject *args) {
    int index;

    if (!PyArg_ParseTuple(args, "i", &index))
        return NULL;

    GameObject* gameObject = game_getGameObject(index);
    return PyLong_FromLong(gameObject->addAnimation());
}

static PyObject * animations_setDelay(PyObject *self, PyObject *args) {
    int gameObjectIndex;
    int animationIndex;
    float delay;

    if (!PyArg_ParseTuple(args, "iif", &gameObjectIndex, &animationIndex, &delay))
        return NULL;

    GameObject* gameObject = game_getGameObject(gameObjectIndex);
    Animation* animation = gameObject->getAnimation(animationIndex);
    animation->setDelay(delay);
    return PyLong_FromLong(gameObject->addAnimation());
}

static PyObject * animations_addFrame(PyObject *self, PyObject *args) {
    int index;
    int animationIndex;
    int x;
    int y;
    int width;
    int height;

    if (!PyArg_ParseTuple(args, "iiiiii", &index, &animationIndex, &x, &y, &width, &height))
        return NULL;

    GameObject* gameObject = game_getGameObject(index);
    gameObject->addAnimationFrame(animationIndex, x, y, width, height);
    Py_RETURN_NONE;
}

static PyObject * animations_addFrames(PyObject *self, PyObject *args) {
    int index;
    int animationIndex;
    int fromX;
    int fromY;
    int toX;
    int toY;
    int width;
    int height;

    if (!PyArg_ParseTuple(args, "iiiiiiii", 
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
    int gameObjectIndex;

    if (!PyArg_ParseTuple(args, "i", &gameObjectIndex))
        return NULL;

    GameObject* gameObject = game_getGameObject(gameObjectIndex);
    int activeAnimationGlobalIndex = gameObject->getActiveAnimationGlobalIndex();
    if (activeAnimationGlobalIndex != -1) {
        game_removeActiveAnimation(activeAnimationGlobalIndex);
        gameObject->stopAnimation();
    }
    Py_RETURN_NONE;
}

static PyObject * animations_play(PyObject *self, PyObject *args)
{
    int gameObjectIndex;
    int animationIndex;

    if (!PyArg_ParseTuple(args, "ii", &gameObjectIndex, &animationIndex))
        return NULL;

    GameObject* gameObject = game_getGameObject(gameObjectIndex);
    if(gameObject->getActiveAnimationLocalIndex() != animationIndex) {
        int activeAnimationGlobalIndex = gameObject->getActiveAnimationGlobalIndex();
        if (activeAnimationGlobalIndex != -1) {
            game_removeActiveAnimation(activeAnimationGlobalIndex);
            gameObject->stopAnimation();
        }
        Animation* animation = gameObject->getAnimation(animationIndex);
        gameObject->playAnimation(game_addActiveAnimation(animation), animationIndex);
    }
    Py_RETURN_NONE;
}

static PyObject * animations_pause(PyObject *self, PyObject *args)
{
    int gameObjectIndex;

    if (!PyArg_ParseTuple(args, "i", &gameObjectIndex))
        return NULL;

    GameObject* gameObject = game_getGameObject(gameObjectIndex);
    gameObject->pauseAnimation();
    Py_RETURN_NONE;
}

static PyObject * animations_resume(PyObject *self, PyObject *args)
{
    int gameObjectIndex;

    if (!PyArg_ParseTuple(args, "i", &gameObjectIndex))
        return NULL;

    GameObject* gameObject = game_getGameObject(gameObjectIndex);
    gameObject->resumeAnimation();
    Py_RETURN_NONE;
}

static PyMethodDef animationsMethods[] = {
    {"play",  animations_play, METH_VARARGS,
     "Plays a game objects animation."},

    {"stop",  animations_stop, METH_VARARGS,
     "Stops a game objects animation."},

    {"pause",  animations_pause, METH_VARARGS,
     "Pauses a game objects animation."},

    {"resume",  animations_resume, METH_VARARGS,
     "Resumes a game objects animation."},

    {"setDelay",  animations_setDelay, METH_VARARGS,
     "Sets the delay between animation frames."},

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
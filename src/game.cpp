#include <Python.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "./gameObject/GameObject.hpp"
using namespace std;

#define GAME_MODULE
#include "game.hpp"

sf::RenderWindow window;
vector<GameObject> gameObjects;

static sf::RenderWindow* game_getWindow() {
    return &window;
}

static GameObject* game_getGameObject(int index) {
    return &(gameObjects.at(index));
}

static PyObject* game_createGameObject(PyObject *self, PyObject *args) 
{
    GameObject gameObject(gameObjects.size());
    gameObjects.push_back(gameObject);
    return PyLong_FromLong(gameObjects.size() - 1);
}

static PyObject* game_init(PyObject *self, PyObject *args)
{
    PyObject *pName, *pModule, *initFunc, *updateFunc, *drawFunc;
    const char *gameFileName;
    const char *gameName;
    int width;
    int height;

    if (!PyArg_ParseTuple(args, "ssII", &gameFileName, &gameName, &width, &height))
        return NULL;

    pName = PyUnicode_DecodeFSDefault(gameFileName);

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        if(PyObject_HasAttrString(pModule, "init")) {
            initFunc = PyObject_GetAttrString(pModule, "init");
            PyObject_CallObject(initFunc, NULL);
            Py_XDECREF(initFunc);
        }
        if (PyObject_HasAttrString(pModule, "update")) {
            updateFunc = PyObject_GetAttrString(pModule, "update");
        } 
        if (PyObject_HasAttrString(pModule, "draw")) {
            drawFunc = PyObject_GetAttrString(pModule, "draw");
        } 
    }
    Py_DECREF(pModule);

    window.create(sf::VideoMode(width, height), gameName);

    sf::Clock clock;
    while (window.isOpen())
    {
        while(clock.getElapsedTime().asSeconds() < (1.0/60.0)){
            continue;
        }
        clock.restart();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (updateFunc) {
            PyObject_CallObject(updateFunc, NULL);
        }

        if (drawFunc) {
            window.clear();
            PyObject_CallObject(drawFunc, NULL);
            window.display();
        }
    }
    
    Py_XDECREF(drawFunc);
    Py_XDECREF(updateFunc);
    Py_RETURN_NONE;
}

static PyMethodDef gameMethods[] = {

    {"init",  game_init, METH_VARARGS,
     "Initializes a SFML window."},

    {"createGameObject",  game_createGameObject, METH_VARARGS,
     "Creates a new game object and returns its global index."},

    {NULL, NULL, 0, NULL} 
};

static struct PyModuleDef gameModule = {
    PyModuleDef_HEAD_INIT,
    "pyzzle.game",
    NULL,
    -1,
    gameMethods
};

PyMODINIT_FUNC PyInit_game(void)
{
    PyObject *module;
    static void *Game_API[Game_API_pointers];
    PyObject *c_api_object;

    module = PyModule_Create(&gameModule);
    if (module == NULL)
        return NULL;

    Game_API[0] = (void *)&game_getWindow;
    Game_API[1] = (void *)&game_getGameObject;

    c_api_object = PyCapsule_New((void *)Game_API, "pyzzle.game._C_API", NULL);

    if (c_api_object != NULL)
        PyModule_AddObject(module, "_C_API", c_api_object);
    return module;
}
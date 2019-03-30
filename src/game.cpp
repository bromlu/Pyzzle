#include <Python.h>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#define GAME_MODULE
#include "game.hpp"
using namespace std;

#define ONE_BILLION (double)1000000000.0

double now(void)
{
  struct timespec current_time;
  clock_gettime(CLOCK_REALTIME, &current_time);
  return current_time.tv_sec + (current_time.tv_nsec / ONE_BILLION);
}

sf::RenderWindow window;

static sf::RenderWindow*
game_getWindow() {
    return &window;
}

PyObject *pName, *pModule, *updateFunc, *drawFunc;

static PyObject *
game_init(PyObject *self, PyObject *args)
{
    const char *gameFileName;
    const char *gameName;
    int width;
    int height;

    if (!PyArg_ParseTuple(args, "ssII", &gameFileName, &gameName, &width, &height))
        return NULL;

    pName = PyUnicode_DecodeFSDefault(gameFileName);

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL && PyObject_HasAttrString(pModule, "update")) {
        updateFunc = PyObject_GetAttrString(pModule, "update");
    } 
    if (pModule != NULL && PyObject_HasAttrString(pModule, "draw")) {
        drawFunc = PyObject_GetAttrString(pModule, "draw");
    } 
    Py_DECREF(pModule);

    window.create(sf::VideoMode(width, height), gameName);

    double last = 0.0;
    while (window.isOpen())
    {
        while(now() - last < (1.0/60.0)){
            continue;
        }
        last = now();
        
        // Close window when needed
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Call update if provided
        if (updateFunc != NULL && PyCallable_Check(updateFunc)) {
            PyObject_CallObject(updateFunc, NULL);
        }

        // Call draw if provided
        if (drawFunc && PyCallable_Check(drawFunc)) {
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

    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef gameModule = {
    PyModuleDef_HEAD_INIT,
    "pyzzle.game",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    gameMethods
};

PyMODINIT_FUNC
PyInit_game(void)
{
    PyObject *module;
    static void *Game_API[Game_API_pointers];
    PyObject *c_api_object;

    module = PyModule_Create(&gameModule);
    if (module == NULL)
        return NULL;

    /* Initialize the C API pointer array */
    Game_API[0] = (void *)&game_getWindow;

    /* Create a Capsule containing the API pointer array's address */
    c_api_object = PyCapsule_New((void *)Game_API, "pyzzle.game._C_API", NULL);

    if (c_api_object != NULL)
        PyModule_AddObject(module, "_C_API", c_api_object);
    return module;
}
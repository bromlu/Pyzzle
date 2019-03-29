#include <Python.h>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include "global.cpp"
using namespace std;

#define ONE_BILLION (double)1000000000.0

double now(void)
{
  struct timespec current_time;
  clock_gettime(CLOCK_REALTIME, &current_time);
  return current_time.tv_sec + (current_time.tv_nsec / ONE_BILLION);
}

PyObject *pName, *pModule, *updateFunc, *drawFunc;

static PyObject *
main_init(PyObject *self, PyObject *args)
{
    const char *mainFileName;
    const char *gameName;
    int width;
    int height;

    if (!PyArg_ParseTuple(args, "ssII", &mainFileName, &gameName, &width, &height))
        return NULL;

    Py_Initialize();

    pName = PyUnicode_DecodeFSDefault(mainFileName);

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

static PyMethodDef mainMethods[] = {

    {"init",  main_init, METH_VARARGS,
     "Initializes a SFML window."},

    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef mainModule = {
    PyModuleDef_HEAD_INIT,
    "main",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    mainMethods
};

PyMODINIT_FUNC
PyInit_main(void)
{
    return PyModule_Create(&mainModule);
}
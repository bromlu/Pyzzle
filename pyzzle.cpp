#include <Python.h>
#include <SFML/Graphics.hpp>

static PyObject *
pyzzle_init(PyObject *self, PyObject *args)
{
    const char *mainFileName;
    const char *gameName;

    if (!PyArg_ParseTuple(args, "ss", &mainFileName, &gameName))
        return NULL;

    PyObject *pName, *pModule, *updateFunc;
    Py_Initialize();

    pName = PyUnicode_DecodeFSDefault(mainFileName);

    pModule = PyImport_Import(pName);
    if (pModule != NULL && PyObject_HasAttrString(pModule, "update")) {
        updateFunc = PyObject_GetAttrString(pModule, "update");
    } 
    Py_DECREF(pName);
    Py_DECREF(pModule);

    sf::RenderWindow window(sf::VideoMode(400, 400), gameName);

    while (window.isOpen())
    {
        // Call update if provided
        if (updateFunc && PyCallable_Check(updateFunc)) {
            PyObject_CallObject(updateFunc, NULL);
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
    
    Py_XDECREF(updateFunc);
    Py_RETURN_NONE;
}

static PyMethodDef PyzzleMethods[] = {

    {"init",  pyzzle_init, METH_VARARGS,
     "Initializes a SFML window."},

    {NULL, NULL, 0, NULL}        /* Sentinel */
};

static struct PyModuleDef pyzzlemodule = {
    PyModuleDef_HEAD_INIT,
    "pyzzle",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    PyzzleMethods
};

PyMODINIT_FUNC
PyInit_pyzzle(void)
{
    return PyModule_Create(&pyzzlemodule);
}
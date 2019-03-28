#include <Python.h>
#include <SFML/Graphics.hpp>

static PyObject *
pyzzle_init(PyObject *self, PyObject *args)
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Isn't my app cool Dr. Denning?!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    
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
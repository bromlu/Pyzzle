#include <Python.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "./../game.hpp"
#include "./../gameObject/GameObject.hpp"
#include <iostream>
using namespace std;

sf::Music music;

static PyObject * audio_loadAudio(PyObject *self, PyObject *args)
{
    const char *MusicFileName;

    if (!PyArg_ParseTuple(args, "s", &MusicFileName))
        return NULL;

    if (!music.openFromFile(MusicFileName)) 
        return NULL;  

    music.play(); 

    Py_RETURN_FALSE;
}

// static PyObject * audio_playAudio(PyObject *self, PyObject *args)
// {
//     int key;

//     if (!PyArg_ParseTuple(args, "i", &key))
//         return NULL;

//     if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key))) {
//         Py_RETURN_TRUE;
//     }

//     Py_RETURN_FALSE;
// }

// static PyObject * audio_pauseAudio(PyObject *self, PyObject *args)
// {
//     int key;

//     if (!PyArg_ParseTuple(args, "i", &key))
//         return NULL;

//     if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key))) {
//         Py_RETURN_TRUE;
//     }

//     Py_RETURN_FALSE;
// }

static PyMethodDef audioMethods[] = {

     //load
    {"loadAudio", audio_loadAudio, METH_VARARGS,
     "Loads audio from file"},

    //  //play
    // {"playAudio", audio_playAudio, METH_VARARGS,
    //  "Plays loaded audio"},
     
    //  //pause
    // {"loadAudio", audio_pauseAudio, METH_VARARGS,
    //  "Pauses loaded audio"},

    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef audioModule = {
    PyModuleDef_HEAD_INIT,
    "pyzzle.audio",
    NULL,
    -1,
    audioMethods
};

PyMODINIT_FUNC PyInit_audio(void)
{
    PyObject *module;

    module = PyModule_Create(&audioModule);
    if (module == NULL)
        return NULL;
    if (import_game() < 0)
        return NULL;
    return module;
}
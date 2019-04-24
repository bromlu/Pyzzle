#include <Python.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "./../game.hpp"
#include "./../gameObject/GameObject.hpp"
#include <iostream>
using namespace std;

vector<sf::Music*> music;
vector<sf::Music*> audio;


static PyObject * audio_loadMusic(PyObject *self, PyObject * args)
{
    const char *MusicFileName;

    if (!PyArg_ParseTuple(args, "s", &MusicFileName))
        return NULL;
    
    long index = music.size();
    music.push_back(new sf::Music());

    if (!music.at(index)->openFromFile(MusicFileName)) {
        cout << "failed to load" << endl;
        return NULL;
    }
    
    return PyLong_FromLong(index);

};

static PyObject * audio_playMusic(PyObject *self, PyObject * args)
{
    int index;

    if (!PyArg_ParseTuple(args, "i", &index))
        return NULL;

    cout << "calling music" << endl;
    music.at(index)->play();
    cout << "playing music" << endl;

    Py_RETURN_FALSE;
};


static PyObject * audio_loadAudio(PyObject *self, PyObject * args)
{
    const char *AudioFileName;

    if (!PyArg_ParseTuple(args, "s", &AudioFileName))
        return NULL;
    
    long index = audio.size();
    audio.push_back(new sf::Music());

    if (!audio.at(index)->openFromFile(AudioFileName)) {
        cout << "failed to load" << endl;
        return NULL;
    }
    
    return PyLong_FromLong(index);

};

static PyObject * audio_playAudio(PyObject *self, PyObject * args)
{
    int index;

    if (!PyArg_ParseTuple(args, "i", &index))
        return NULL;

    cout << "calling music" << endl;
    audio.at(index)->play();
    cout << "playing music" << endl;

    Py_RETURN_FALSE;
};


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

    //load Music
    {"loadMusic", audio_loadMusic, METH_VARARGS,
     "Loads music from file"},

    //play
    {"playMusic", audio_playMusic, METH_VARARGS,
     "Plays loaded music"},
     
     //load Audio
    {"loadAudio", audio_loadAudio, METH_VARARGS,
     "Loads audio from file"},

    //play
    {"playAudio", audio_playAudio, METH_VARARGS,
     "Plays loaded audio"},
     
    //  //pause
    // {"loadAudio", audio_pauseAudio, METH_VARARGS,
    //  "Pauses loaded audio"},

    {NULL}
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
};
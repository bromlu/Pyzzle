#include <Python.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "./../game.hpp"
#include "./../gameObject/GameObject.hpp"
#include <iostream>
using namespace std;

vector<sf::Music*> music;
vector<sf::SoundBuffer> audioBuffers;
vector<sf::Sound> audio;
sf::Sound sound;
sf::SoundBuffer buffer;


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

static PyObject * audio_loopMusic(PyObject *self, PyObject * args)
{
    int index;

    if (!PyArg_ParseTuple(args, "i", &index))
        return NULL;

    music.at(index)->setLoop(true);

    Py_RETURN_FALSE;
};

static PyObject * audio_playMusic(PyObject *self, PyObject * args)
{
    int index;

    if (!PyArg_ParseTuple(args, "i", &index))
        return NULL;

    if(music.at(index)->getStatus() != sf::SoundSource::Status::Playing) {
        music.at(index)->play();
    }

    Py_RETURN_FALSE;
};

static PyObject * audio_pauseMusic(PyObject *self, PyObject *args)
{
    int index;

    if (!PyArg_ParseTuple(args, "i", &index))
        return NULL;

    music.at(index)->pause();

    Py_RETURN_FALSE;
}

static PyObject * audio_stopMusic(PyObject *self, PyObject *args)
{
    int index;

    if (!PyArg_ParseTuple(args, "i", &index))
        return NULL;

    music.at(index)->stop();

    Py_RETURN_FALSE;
}

static PyObject * audio_loadAudio(PyObject *self, PyObject * args)
{
    const char *AudioFileName;

    if (!PyArg_ParseTuple(args, "s", &AudioFileName))
        return NULL;
    
    long index = audioBuffers.size();

    audioBuffers.push_back(sf::SoundBuffer());
    if (!audioBuffers.at(index).loadFromFile(AudioFileName)) {
        cout << "failed to load" << endl;
        return NULL;
    }
    audio.push_back(sf::Sound(audioBuffers.at(index)));

    return PyLong_FromLong(index);
};

static PyObject * audio_playAudio(PyObject *self, PyObject * args)
{
    int index;

    if (!PyArg_ParseTuple(args, "i", &index))
        return NULL;

    if(audio.at(index).getStatus() != sf::SoundSource::Status::Playing) {
        audio.at(index).play();
    }

    Py_RETURN_FALSE;
};

static PyObject * audio_pauseAudio(PyObject *self, PyObject *args)
{
    int index;

    if (!PyArg_ParseTuple(args, "i", &index))
        return NULL;

    audio.at(index).pause();

    Py_RETURN_FALSE;
}

static PyObject * audio_stopAudio(PyObject *self, PyObject *args)
{
    int index;

    if (!PyArg_ParseTuple(args, "i", &index))
        return NULL;

    audio.at(index).stop();

    Py_RETURN_FALSE;
}

static PyMethodDef audioMethods[] = {

    {"loadMusic", audio_loadMusic, METH_VARARGS,
     "Loads music from file"},

    {"loopMusic", audio_loopMusic, METH_VARARGS,
     "Loops music from file"},

    {"playMusic", audio_playMusic, METH_VARARGS,
     "Plays loaded music"},

    {"pauseMusic", audio_pauseMusic, METH_VARARGS,
     "Pauses loaded music"},

    {"stopMusic", audio_stopMusic, METH_VARARGS,
     "Stops loaded music"},
     
    {"loadAudio", audio_loadAudio, METH_VARARGS,
     "Loads audio from file"},

    {"playAudio", audio_playAudio, METH_VARARGS,
     "Plays loaded audio"},
     
    {"pauseAudio", audio_pauseAudio, METH_VARARGS,
     "Pauses loaded audio"},

    {"stopAudio", audio_stopAudio, METH_VARARGS,
     "Stops loaded audio"},

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
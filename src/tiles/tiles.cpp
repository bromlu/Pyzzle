#include <Python.h>
#include <SFML/Graphics.hpp>
#include "./../game.hpp"
#include "./../gameObject/GameObject.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

vector<sf::Texture> textures;

static PyObject * tiles_setTileWidth(PyObject *self, PyObject *args)
{
    float width;

    if (!PyArg_ParseTuple(args, "f", &width))
        return NULL;

    game_setTileWidth(width);
    Py_RETURN_NONE;
}

static PyObject * tiles_setTileHeight(PyObject *self, PyObject *args)
{
    float height;

    if (!PyArg_ParseTuple(args, "f", &height))
        return NULL;

    game_setTileHeight(height);
    Py_RETURN_NONE;
}

static PyObject * tiles_setTileFrame(PyObject *self, PyObject *args)
{
    int x;
    int y;
    int width;
    int height;

    if (!PyArg_ParseTuple(args, "iiii", &x, &y, &width, &height))
        return NULL;

    game_setTileFrame(sf::IntRect(x, y, width, height));
    Py_RETURN_NONE;
}

static PyObject * tiles_addTileType(PyObject *self, PyObject *args)
{
    const char* fileName;

    if (!PyArg_ParseTuple(args, "s", &fileName))
        return NULL;

    sf::Texture texture;
    texture.loadFromFile(fileName);
    textures.push_back(texture);
    Py_RETURN_NONE;
}

static PyObject * tiles_loadFromTextFile(PyObject *self, PyObject *args)
{
    const char* fileName;

    if (!PyArg_ParseTuple(args, "s", &fileName))
        return NULL;

    ifstream mapFile;
    char character;
    mapFile.open(fileName);
    if (mapFile.is_open()) {
        string currentNumber = "";
        int x = 0;
        int y = 0;
        while ( mapFile.get(character) ) {
            if(isspace(character)) {
                if(currentNumber.length() != 0) {
                    int index = stoi(currentNumber);
                    game_addTile(&textures.at(index), x, y);
                    currentNumber = "";
                }
                if(character == '\n') {
                    y++;
                    x = 0;
                } else {
                    x++;
                }
            } else {
                currentNumber += character;
            }
        }
        if(currentNumber.length() != 0) {
            int index = stoi(currentNumber);
            game_addTile(&textures.at(index), x, y);
        }
        mapFile.close();
    }

    Py_RETURN_NONE;
}

static PyMethodDef tilesMethods[] = {
    {"setTileWidth",  tiles_setTileWidth, METH_VARARGS,
     "Sets the width of all tiles."},

    {"setTileHeight",  tiles_setTileHeight, METH_VARARGS,
     "sets the height of all tiles."},

    {"setTileFrame",  tiles_setTileFrame, METH_VARARGS,
     "sets the frame of tiles to be displayed."},

    {"addTileType",  tiles_addTileType, METH_VARARGS,
     "sets the height of all tiles."},

    {"loadFromTextFile",  tiles_loadFromTextFile, METH_VARARGS,
     "sets the height of all tiles."},

    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef tilesModule = {
    PyModuleDef_HEAD_INIT,
    "pyzzle.tiles",
    NULL,
    -1,
    tilesMethods
};

PyMODINIT_FUNC PyInit_tiles(void)
{
    PyObject *module;

    module = PyModule_Create(&tilesModule);
    if (module == NULL)
        return NULL;
    if (import_game() < 0)
        return NULL;
    return module;
}
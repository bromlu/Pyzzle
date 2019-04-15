#include <Python.h>
#include <SFML/Graphics.hpp>
#include "./../game.hpp"
#include "./../gameObject/GameObject.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

vector<sf::Texture> textures;
vector<vector<sf::Sprite> > tiles;
sf::Rect<float> tileFrame(0.0,0.0,0.0,0.0);
float TILE_WIDTH = 32.0;
float TILE_HEIGHT = 32.0;

static void addTile(sf::Texture* tileTexture, int x, int y) {
    sf::Sprite sprite(*tileTexture);
    sprite.setPosition(x * TILE_WIDTH, y * TILE_HEIGHT);
    sprite.setScale(
        TILE_WIDTH / sprite.getLocalBounds().width, 
        TILE_HEIGHT / sprite.getLocalBounds().height);
    if (int(tiles.size()) == y) {
        tiles.push_back(vector<sf::Sprite>());
    }
    tiles.at(y).push_back(sprite);
}

static PyObject * tiles_setTileWidth(PyObject *self, PyObject *args)
{
    float width;

    if (!PyArg_ParseTuple(args, "f", &width))
        return NULL;

    TILE_WIDTH = width;
    Py_RETURN_NONE;
}

static PyObject * tiles_setTileHeight(PyObject *self, PyObject *args)
{
    float height;

    if (!PyArg_ParseTuple(args, "f", &height))
        return NULL;

    TILE_HEIGHT = height;
    Py_RETURN_NONE;
}

static PyObject * tiles_setTileFrame(PyObject *self, PyObject *args)
{
    float x;
    float y;
    float width;
    float height;

    if (!PyArg_ParseTuple(args, "ffff", &x, &y, &width, &height))
        return NULL;

    tileFrame = sf::Rect<float>(x, y, width, height);
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
                    addTile(&textures.at(index), x, y);
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
            addTile(&textures.at(index), x, y);
        }
        mapFile.close();
    }

    Py_RETURN_NONE;
}

static PyObject * tiles_draw(PyObject *self, PyObject *args)
{
    for (int y = tileFrame.top; y < tileFrame.height + tileFrame.top; y++) {
        for (int x = tileFrame.left; x < tileFrame.width + tileFrame.left; x++) {
            tiles.at(floor(y)).at(floor(x)).setPosition((x - tileFrame.left) * TILE_WIDTH, (y - tileFrame.top) * TILE_HEIGHT);
            game_getWindow()->draw(tiles.at(floor(y)).at(floor(x)));
        }
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
     "Adds a new tile type."},

    {"loadFromTextFile",  tiles_loadFromTextFile, METH_VARARGS,
     "Loads the tiles from a text file."},

    {"draw",  tiles_draw, METH_VARARGS,
     "Draws the tiles."},


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
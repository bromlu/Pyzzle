#include <Python.h>
#include <SFML/Graphics.hpp>
#include "./../game.hpp"
#include "./../gameObject/GameObject.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

vector<sf::Texture> textures;
sf::Texture tileMap;
sf::Sprite tileMapSprite;
float TILE_WIDTH = 32.0;
float TILE_HEIGHT = 32.0;
int MAP_WIDTH = 0;
int MAP_HEIGHT = 0;

void setScale() {
    tileMapSprite.setScale(
    TILE_WIDTH / (tileMapSprite.getLocalBounds().width / MAP_WIDTH), 
    TILE_HEIGHT / (tileMapSprite.getLocalBounds().height / MAP_HEIGHT));
}

static PyObject * tiles_setTileWidth(PyObject *self, PyObject *args)
{
    float width;

    if (!PyArg_ParseTuple(args, "f", &width))
        return NULL;

    TILE_WIDTH = width;
    setScale();
    Py_RETURN_NONE;
}

static PyObject * tiles_setTileHeight(PyObject *self, PyObject *args)
{
    float height;

    if (!PyArg_ParseTuple(args, "f", &height))
        return NULL;

    TILE_HEIGHT = height;
    setScale();
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

    sf::FloatRect localBounds = tileMapSprite.getLocalBounds();
    sf::FloatRect globalBounds = tileMapSprite.getGlobalBounds();
    float scalerX = localBounds.width / globalBounds.width;
    float scalerY = localBounds.height / globalBounds.height;
    tileMapSprite.setTextureRect(sf::IntRect(int(x * scalerX), int(y * scalerY), width, height));
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
    int width;
    int height;

    if (!PyArg_ParseTuple(args, "sii", &fileName, &width, &height))
        return NULL;

    MAP_WIDTH = width;
    MAP_HEIGHT = height;
    tileMap.create(width * textures.at(0).getSize().x, height * textures.at(0).getSize().y);

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
                    sf::Texture tileTexture = textures.at(index);
                    sf::Vector2u size = tileTexture.getSize();
                    tileMap.update(tileTexture, x * size.x, y * size.y);
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
            sf::Texture tileTexture = textures.at(index);
            sf::Vector2u size = tileTexture.getSize();
            tileMap.update(tileTexture, x * size.x, y * size.y);
        }
        mapFile.close();
    }

    tileMapSprite.setTexture(tileMap);
    setScale();

    Py_RETURN_NONE;
}

static PyObject * tiles_draw(PyObject *self, PyObject *args)
{
    game_getWindow()->draw(tileMapSprite);
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
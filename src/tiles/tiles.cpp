#include <Python.h>
#include <SFML/Graphics.hpp>
#include "./../game.hpp"
#include "./../gameObject/GameObject.hpp"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

vector<sf::Image> images;
map<string, int> colorMap;
sf::Image inputMap;
sf::Texture tileMap;
sf::Sprite tileMapSprite;
float TILE_WIDTH = 32.0;
float TILE_HEIGHT = 32.0;
int MAP_WIDTH = 0;
int MAP_HEIGHT = 0;

void setScale() {
    tileMapSprite.setScale(
    TILE_WIDTH / images.at(0).getSize().x, 
    TILE_HEIGHT / images.at(0).getSize().y);
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

static PyObject * tiles_addTextTileType(PyObject *self, PyObject *args)
{
    const char* fileName;

    if (!PyArg_ParseTuple(args, "s", &fileName))
        return NULL;

    sf::Image image;
    image.loadFromFile(fileName);
    images.push_back(image);
    Py_RETURN_NONE;
}

static PyObject * tiles_addPngTileType(PyObject *self, PyObject *args)
{
    const char* fileName;
    int R;
    int G;
    int B;

    if (!PyArg_ParseTuple(args, "siii", &fileName, &R, &G, &B))
        return NULL;

    colorMap.insert(pair<string, int>(to_string(R) + to_string(G) + to_string(B), images.size()));
    
    sf::Image image;
    image.loadFromFile(fileName);
    images.push_back(image);
    Py_RETURN_NONE;
}

static PyObject * tiles_loadFromText(PyObject *self, PyObject *args)
{
    const char* fileName;
    int width;
    int height;

    if (!PyArg_ParseTuple(args, "sii", &fileName, &width, &height))
        return NULL;

    MAP_WIDTH = width;
    MAP_HEIGHT = height;
    tileMap.create(width * images.at(0).getSize().x, height * images.at(0).getSize().y);

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
                    sf::Image tileImage = images.at(index);
                    sf::Vector2u size = tileImage.getSize();
                    tileMap.update(tileImage, x * size.x, y * size.y);
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
            sf::Image tileImage = images.at(index);
            sf::Vector2u size = tileImage.getSize();
            tileMap.update(tileImage, x * size.x, y * size.y);
        }
        mapFile.close();
    }

    tileMapSprite.setTexture(tileMap);
    setScale();

    Py_RETURN_NONE;
}

static PyObject * tiles_loadFromPng(PyObject *self, PyObject *args)
{
    const char* fileName;
    int width;
    int height;

    if (!PyArg_ParseTuple(args, "sii", &fileName, &width, &height))
        return NULL;

    inputMap.loadFromFile(fileName);

    const sf::Uint8* pixels = inputMap.getPixelsPtr();
    sf::Vector2u size = inputMap.getSize();

    MAP_WIDTH = width;
    MAP_HEIGHT = height;
    tileMap.create(width * images.at(0).getSize().x, height * images.at(0).getSize().y);

    for(unsigned int i = 0; i < size.x * size.y * 4; i += 4) {
        string key = to_string(pixels[i]) + to_string(pixels[(i)+1]) + to_string(pixels[(i)+2]);
        sf::Image tileImage = images.at(colorMap[key]);
        sf::Vector2u imagesize = tileImage.getSize();
        tileMap.update(tileImage, int(i / 4 % size.x) * imagesize.x, int(i / 4 / size.y) * imagesize.y);
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

static PyObject * tiles_objectInTile(PyObject *self, PyObject *args)
{
    int gameObjectIndex;
    int R;
    int G;
    int B;

    if (!PyArg_ParseTuple(args, "iiii", &gameObjectIndex, &R, &G, &B))
        return NULL;

    GameObject* gameObject = game_getGameObject(gameObjectIndex);
    sf::Sprite* sprite = gameObject->getSprite();
    sf::Vector2f objectPosition = gameObject->getPosition();
    sf::IntRect objectFrame = sprite->getTextureRect();
    sf::Vector2f scale = sprite->getScale();

    const sf::Uint8* pixels = inputMap.getPixelsPtr();
    sf::Vector2u size = inputMap.getSize();
    int length = size.x * size.y * 4;

    sf::IntRect frame = tileMapSprite.getTextureRect();

    sf::FloatRect localBounds = tileMapSprite.getLocalBounds();
    sf::FloatRect globalBounds = tileMapSprite.getGlobalBounds();
    float scalerX = localBounds.width / globalBounds.width;
    float scalerY = localBounds.height / globalBounds.height;

    for(int col = objectPosition.y; col <= objectFrame.height * scale.y + objectPosition.y; col += TILE_HEIGHT) {
        for(int row = objectPosition.x; row <= objectFrame.width * scale.x + objectPosition.x; row += TILE_WIDTH) {
            int x = (int(row) + frame.left / scalerX) / TILE_WIDTH;
            int y = (int(col) + frame.top / scalerY) / TILE_HEIGHT;
            int i = (x + (y * size.x)) * 4;

            if ( i < length && x > 0 && y > 0) {
                if (R == pixels[i] && G == pixels[i+1] && B == pixels[i+2]) {
                    if (gameObject->contains(sf::Vector2f(row, col))) {
                        Py_RETURN_TRUE;
                    }
                }
            }
        }
    }
    Py_RETURN_FALSE;
}

static PyObject * tiles_pointInTile(PyObject *self, PyObject *args)
{
    float pointX;
    float pointY;
    int R;
    int G;
    int B;

    if (!PyArg_ParseTuple(args, "ffiii", &pointX, &pointY, &R, &G, &B))
        return NULL;

    const sf::Uint8* pixels = inputMap.getPixelsPtr();
    sf::Vector2u size = inputMap.getSize();
    int length = size.x * size.y * 4;

    sf::IntRect frame = tileMapSprite.getTextureRect();

    sf::FloatRect localBounds = tileMapSprite.getLocalBounds();
    sf::FloatRect globalBounds = tileMapSprite.getGlobalBounds();
    float scalerX = localBounds.width / globalBounds.width;
    float scalerY = localBounds.height / globalBounds.height;

    int x = (int(pointX) + frame.left / scalerX) / TILE_WIDTH;
    int y = (int(pointY) + frame.top / scalerY) / TILE_HEIGHT;
    int i = (x + (y * size.x)) * 4;

    if ( i > length || x < 0 || y < 0) {
        Py_RETURN_FALSE;
    } else if (R == pixels[i] && G == pixels[i+1] && B == pixels[i+2]) {
        Py_RETURN_TRUE;
    }
    Py_RETURN_FALSE;
}

static PyMethodDef tilesMethods[] = {
    {"setTileWidth",  tiles_setTileWidth, METH_VARARGS,
     "Sets the width of all tiles."},

    {"setTileHeight",  tiles_setTileHeight, METH_VARARGS,
     "sets the height of all tiles."},

    {"setTileFrame",  tiles_setTileFrame, METH_VARARGS,
     "sets the frame of tiles to be displayed."},

    {"addTextTileType",  tiles_addTextTileType, METH_VARARGS,
     "Adds a new tile type."},

    {"addPngTileType",  tiles_addPngTileType, METH_VARARGS,
     "Adds a new tile type."},

    {"loadFromText",  tiles_loadFromText, METH_VARARGS,
     "Loads the tiles from a text file."},

    {"loadFromPng",  tiles_loadFromPng, METH_VARARGS,
     "Loads the tiles from a text file."},

    {"draw",  tiles_draw, METH_VARARGS,
     "Draws the tiles."},

    {"objectInTile",  tiles_objectInTile, METH_VARARGS,
     "Returns true if the game object is inside any tile of given type."},

    {"pointInTile",  tiles_pointInTile, METH_VARARGS,
     "Returns true if the game point is inside any tile of given type."},

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
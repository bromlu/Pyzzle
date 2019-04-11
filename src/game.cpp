#include <Python.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "./gameObject/GameObject.hpp"
#include "./gameObject/Animation.hpp"
#include <tuple>
using namespace std;

#define GAME_MODULE
#include "game.hpp"

sf::RenderWindow window;
vector<GameObject*> gameObjects;
vector<Animation*> activeAnimations;
vector<vector<sf::Sprite> > tiles;
sf::IntRect tileFrame(0,0,0,0);
float TILE_WIDTH = 32.0;
float TILE_HEIGHT = 32.0;

static sf::RenderWindow* game_getWindow() {
    return &window;
}

static GameObject* game_getGameObject(int index) {
    return gameObjects.at(index);
}

static int game_addActiveAnimation(Animation* animation) {
    activeAnimations.push_back(animation);
    return activeAnimations.size() - 1;
}

static void game_removeActiveAnimation(int index) {
    activeAnimations.erase(activeAnimations.begin()+index);
}

static void game_addTile(sf::Texture* tileTexture, int x, int y) {
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

static void game_setTileFrame(sf::IntRect rect) {
    tileFrame = rect;
}

static void game_setTileWidth(float width) {
    TILE_WIDTH = width;
}

static void game_setTileHeight(float height) {
    TILE_HEIGHT = height;
}

static PyObject* game_createGameObject(PyObject *self, PyObject *args) 
{
    gameObjects.push_back(new GameObject(gameObjects.size()));
    return PyLong_FromLong(gameObjects.size() - 1);
}

static PyObject* game_moveGameObject(PyObject *self, PyObject *args) 
{
    int index;
    float x;
    float y;

    if (!PyArg_ParseTuple(args, "iff", &index, &x, &y))
        return NULL;

    gameObjects.at(index)->move(sf::Vector2f(x, y));
    Py_RETURN_NONE;
}

static PyObject* game_setGameObjectPosition(PyObject *self, PyObject *args) 
{
    int index;
    float x;
    float y;

    if (!PyArg_ParseTuple(args, "iff", &index, &x, &y))
        return NULL;

    gameObjects.at(index)->setPosition(sf::Vector2f(x, y));
    Py_RETURN_NONE;
}

static PyObject* game_getGameObjectPosition(PyObject *self, PyObject *args) 
{
    int index;
    PyObject* positionTuple = PyTuple_New(2);

    if (!PyArg_ParseTuple(args, "i", &index))
        return NULL;

    sf::Vector2f position = gameObjects.at(index)->getPosition();
    PyTuple_SetItem(positionTuple, 0, PyFloat_FromDouble(double(position.x)));
    PyTuple_SetItem(positionTuple, 1, PyFloat_FromDouble(double(position.y)));
    return positionTuple;
}

static PyObject* game_init(PyObject *self, PyObject *args)
{
    PyObject *pName, *pModule, *initFunc, *updateFunc, *drawFunc;
    const char *gameFileName;
    const char *gameName;
    int width;
    int height;

    if (!PyArg_ParseTuple(args, "ssII", &gameFileName, &gameName, &width, &height))
        return NULL;

    pName = PyUnicode_DecodeFSDefault(gameFileName);

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        if(PyObject_HasAttrString(pModule, "init")) {
            initFunc = PyObject_GetAttrString(pModule, "init");
            PyObject_CallObject(initFunc, NULL);
            Py_XDECREF(initFunc);
        }
        if (PyObject_HasAttrString(pModule, "update")) {
            updateFunc = PyObject_GetAttrString(pModule, "update");
        } 
        if (PyObject_HasAttrString(pModule, "draw")) {
            drawFunc = PyObject_GetAttrString(pModule, "draw");
        } 
    }
    Py_DECREF(pModule);

    window.create(sf::VideoMode(width, height), gameName);

    sf::Clock clock;
    while (window.isOpen())
    {
        while(clock.getElapsedTime().asSeconds() < (1.0/60.0)){
            continue;
        }
        clock.restart();
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (updateFunc) {
            PyObject_CallObject(updateFunc, NULL);
        }

        for (vector<Animation*>::iterator it = activeAnimations.begin(); it != activeAnimations.end(); ++it) {
            (*it)->animate();
        }

        if (drawFunc) {
            window.clear();
            for (int y = tileFrame.top; y < tileFrame.height + tileFrame.top; y++) {
                for (int x = tileFrame.left; x < tileFrame.width + tileFrame.left; x++) {
                    tiles.at(y).at(x).setPosition((x - tileFrame.left) * TILE_WIDTH, (y - tileFrame.top) * TILE_HEIGHT);
                    window.draw(tiles.at(y).at(x));
                }
            }
            PyObject_CallObject(drawFunc, NULL);
            window.display();
        }
    }
    
    Py_XDECREF(drawFunc);
    Py_XDECREF(updateFunc);
    Py_RETURN_NONE;
}

static PyMethodDef gameMethods[] = {

    {"init",  game_init, METH_VARARGS,
     "Initializes a SFML window."},

    {"createGameObject",  game_createGameObject, METH_VARARGS,
     "Creates a new game object and returns its global index."},

    {"moveGameObject",  game_moveGameObject, METH_VARARGS,
     "Creates a new game object and returns its global index."},

    {"setGameObjectPosition",  game_setGameObjectPosition, METH_VARARGS,
     "Creates a new game object and returns its global index."},

    {"getGameObjectPosition",  game_getGameObjectPosition, METH_VARARGS,
     "Creates a new game object and returns its global index."},

    {NULL, NULL, 0, NULL} 
};

static struct PyModuleDef gameModule = {
    PyModuleDef_HEAD_INIT,
    "pyzzle.game",
    NULL,
    -1,
    gameMethods
};

PyMODINIT_FUNC PyInit_game(void)
{
    PyObject *module;
    static void *Game_API[Game_API_pointers];
    PyObject *c_api_object;

    module = PyModule_Create(&gameModule);
    if (module == NULL)
        return NULL;

    Game_API[0] = (void *)&game_getWindow;
    Game_API[1] = (void *)&game_getGameObject;
    Game_API[2] = (void *)&game_addActiveAnimation;
    Game_API[3] = (void *)&game_removeActiveAnimation;
    Game_API[4] = (void *)&game_addTile;
    Game_API[5] = (void *)&game_setTileFrame;
    Game_API[6] = (void *)&game_setTileWidth;
    Game_API[7] = (void *)&game_setTileHeight;

    c_api_object = PyCapsule_New((void *)Game_API, "pyzzle.game._C_API", NULL);

    if (c_api_object != NULL)
        PyModule_AddObject(module, "_C_API", c_api_object);
    return module;
}
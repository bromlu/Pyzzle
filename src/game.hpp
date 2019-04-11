#include <Python.h>
#ifndef GAMEMODULE_H
#define GAMEMODULE_H
#ifdef __cplusplus
extern "C" {
#endif

#define Game_GetWindow_NUM 0
#define Game_GetWindow_RETURN sf::RenderWindow*
#define Game_GetWindow_PROTO ()

#define Game_GetGameObject_NUM 1
#define Game_GetGameObject_RETURN GameObject*
#define Game_GetGameObject_PROTO (int index)

#define Game_addActiveAnimation_NUM 2
#define Game_addActiveAnimation_RETURN int
#define Game_addActiveAnimation_PROTO (Animation* animation)

#define Game_removeActiveAnimation_NUM 3
#define Game_removeActiveAnimation_RETURN void
#define Game_removeActiveAnimation_PROTO (int index)

#define Game_addTile_NUM 4
#define Game_addTile_RETURN void
#define Game_addTile_PROTO (sf::Texture* tileTexture, int x, int y)

#define Game_setTileFrame_NUM 5
#define Game_setTileFrame_RETURN void
#define Game_setTileFrame_PROTO (sf::Rect<float> rect)

#define Game_setTileWidth_NUM 6
#define Game_setTileWidth_RETURN void
#define Game_setTileWidth_PROTO (float width)

#define Game_setTileHeight_NUM 7
#define Game_setTileHeight_RETURN void
#define Game_setTileHeight_PROTO (float height)

#define Game_API_pointers 8

#ifdef GAME_MODULE

static Game_GetWindow_RETURN game_getWindow Game_GetWindow_PROTO;
static Game_GetGameObject_RETURN game_GetGameObject Game_GetGameObject_PROTO;
static Game_addActiveAnimation_RETURN game_addActiveAnimation Game_addActiveAnimation_PROTO;
static Game_removeActiveAnimation_RETURN game_removeActiveAnimation Game_removeActiveAnimation_PROTO;
static Game_addTile_RETURN game_addTile Game_addTile_PROTO;
static Game_setTileFrame_RETURN game_setTileFrame Game_setTileFrame_PROTO;
static Game_setTileWidth_RETURN game_setTileWidth Game_setTileWidth_PROTO;
static Game_setTileHeight_RETURN game_setTileHeight Game_setTileHeight_PROTO;

#else

static void **Game_API;

#define game_getWindow \
 (*(Game_GetWindow_RETURN (*)Game_GetWindow_PROTO) Game_API[Game_GetWindow_NUM])

#define game_getGameObject \
 (*(Game_GetGameObject_RETURN (*)Game_GetGameObject_PROTO) Game_API[Game_GetGameObject_NUM])

#define game_addActiveAnimation \
 (*(Game_addActiveAnimation_RETURN (*)Game_addActiveAnimation_PROTO) Game_API[Game_addActiveAnimation_NUM])

#define game_removeActiveAnimation \
 (*(Game_removeActiveAnimation_RETURN (*)Game_removeActiveAnimation_PROTO) Game_API[Game_removeActiveAnimation_NUM])

#define game_addTile \
 (*(Game_addTile_RETURN (*)Game_addTile_PROTO) Game_API[Game_addTile_NUM])

#define game_setTileFrame \
 (*(Game_setTileFrame_RETURN (*)Game_setTileFrame_PROTO) Game_API[Game_setTileFrame_NUM])

#define game_setTileWidth \
 (*(Game_setTileWidth_RETURN (*)Game_setTileWidth_PROTO) Game_API[Game_setTileWidth_NUM])

#define game_setTileHeight \
 (*(Game_setTileHeight_RETURN (*)Game_setTileHeight_PROTO) Game_API[Game_setTileHeight_NUM])

static int
import_game(void)
{
    Game_API = (void **)PyCapsule_Import("pyzzle.game._C_API", 0);
    return (Game_API != NULL) ? 0 : -1;
}

#endif

#ifdef __cplusplus
}
#endif

#endif
#include <Python.h>
#ifndef GAMEMODULE_H
#define GAMEMODULE_H
#ifdef __cplusplus
extern "C" {
#endif

#define Game_GetWindow_NUM 0
#define Game_GetWindow_RETURN sf::RenderWindow*
#define Game_GetWindow_PROTO ()

#define Game_GetRectangle_NUM 1
#define Game_GetRectangle_RETURN sf::RectangleShape*
#define Game_GetRectangle_PROTO (int index)

#define Game_AddRectangle_NUM 2
#define Game_AddRectangle_RETURN long
#define Game_AddRectangle_PROTO ()

#define Game_API_pointers 3

#ifdef GAME_MODULE

static Game_GetWindow_RETURN game_getWindow Game_GetWindow_PROTO;
static Game_GetRectangle_RETURN game_GetRectangle Game_GetRectangle_PROTO;
static Game_AddRectangle_RETURN game_AddRectangle Game_AddRectangle_PROTO;

#else

static void **Game_API;

#define game_getWindow \
 (*(Game_GetWindow_RETURN (*)Game_GetWindow_PROTO) Game_API[Game_GetWindow_NUM])

#define game_getRectangle \
 (*(Game_GetRectangle_RETURN (*)Game_GetRectangle_PROTO) Game_API[Game_GetRectangle_NUM])

#define game_addRectangle \
 (*(Game_AddRectangle_RETURN (*)Game_AddRectangle_PROTO) Game_API[Game_AddRectangle_NUM])

static int
import_game(void)
{
    Game_API = (void **)PyCapsule_Import("pyzzle.game._C_API", 0);
    return (Game_API != nullptr) ? 0 : -1;
}

#endif

#ifdef __cplusplus
}
#endif

#endif
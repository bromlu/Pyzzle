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

#define Game_API_pointers 3

#ifdef GAME_MODULE

static Game_GetWindow_RETURN game_getWindow Game_GetWindow_PROTO;
static Game_GetGameObject_RETURN game_GetGameObject Game_GetGameObject_PROTO;

#else

static void **Game_API;

#define game_getWindow \
 (*(Game_GetWindow_RETURN (*)Game_GetWindow_PROTO) Game_API[Game_GetWindow_NUM])

#define game_getGameObject \
 (*(Game_GetGameObject_RETURN (*)Game_GetGameObject_PROTO) Game_API[Game_GetGameObject_NUM])

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
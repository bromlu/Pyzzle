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

#define Game_API_pointers 4

#ifdef GAME_MODULE

static Game_GetWindow_RETURN game_getWindow Game_GetWindow_PROTO;
static Game_GetGameObject_RETURN game_GetGameObject Game_GetGameObject_PROTO;
static Game_addActiveAnimation_RETURN game_addActiveAnimation Game_addActiveAnimation_PROTO;
static Game_removeActiveAnimation_RETURN game_removeActiveAnimation Game_removeActiveAnimation_PROTO;

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
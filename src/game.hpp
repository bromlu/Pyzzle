#include <Python.h>
#ifndef GAMEMODULE_H
#define GAMEMODULE_H
#ifdef __cplusplus
extern "C" {
#endif

#define Game_System_NUM 0
#define Game_System_RETURN sf::RenderWindow*
#define Game_System_PROTO ()

#define Game_API_pointers 1

#ifdef GAME_MODULE

static Game_System_RETURN game_getWindow Game_System_PROTO;

#else

static void **Game_API;

#define game_getWindow \
 (*(Game_System_RETURN (*)Game_System_PROTO) Game_API[Game_System_NUM])

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
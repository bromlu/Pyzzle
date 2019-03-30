#include <Python.h>
#ifndef Py_GAMEMODULE_H
#define Py_GAMEMODULE_H
#ifdef __cplusplus
extern "C" {
#endif

/* Header file for gameModule */

/* C API functions */
#define Game_System_NUM 0
#define Game_System_RETURN sf::RenderWindow*
#define Game_System_PROTO ()

/* Total number of C API pointers */
#define Game_API_pointers 1


#ifdef GAME_MODULE
/* This section is used when compiling gamemodule.c */
static Game_System_RETURN game_getWindow Game_System_PROTO;
static sf::RenderWindow* game_getWindow();

#else
/* This section is used in modules that use gamemodule's API */

static void **Game_API;

#define game_getWindow \
 (*(Game_System_RETURN (*)Game_System_PROTO) Game_API[Game_System_NUM])

/* Return -1 on error, 0 on success.
 * PyCapsule_Import will set an exception if there's an error.
 */
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

#endif /* !defined(Py_GAMEMODULE_H) */
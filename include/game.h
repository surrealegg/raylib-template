#ifndef GAME_H
#define GAME_H

#ifdef __EMSCRIPTEN__
#include <emscripten/html5.h>
#endif

#include <raylib.h>

#ifdef __cplusplus
extern "C" {
#endif

void MainLoop(void);

#ifdef __cplusplus
}
#endif

#endif // GAME_H

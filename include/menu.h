#ifndef menu_h
#define menu_h
#include <SDL3/SDL_video.h>
#include "sound.h"
#define Menu_widht 1280
#define Menu_height 720



void AfficheMenu( SDL_Window *win, int ListePions[12], AudioStreamInstance* bg_audioStreamInstance);
#endif // menu_h

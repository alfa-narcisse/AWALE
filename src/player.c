#include "player.h"
#include "outils.h"
#include "event.h"
#include <stdbool.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>


// Ici, vous pouvez implémenter des fonctions liées aux joueurs,
// comme la gestion des tours, les interactions avec l'IA, etc.

void executePlayerCommand(
    SDL_Event *event,
    SDL_Renderer * renderer,
    TTF_Font* police,
    SDL_Texture* plateauTexture,
    int PlateauList[12],
    int POS_TROUS[12][2],
    bool* player1Turn,
    int* scorePlayer1,
    int* scorePlayer2
) {
    int p = handleMouseButtonDownEvent(event, *player1Turn, PlateauList,POS_TROUS);
    if (p!=-1){
        doTheMoveDisplay(PlateauList,p, renderer,police,plateauTexture,player1Turn,scorePlayer1,scorePlayer2);
        *player1Turn = !*player1Turn;
    }
 }
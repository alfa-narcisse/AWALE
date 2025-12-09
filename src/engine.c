#include <SDL3/SDL.h>
#include <stdbool.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
#include "engine.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define FONT_PATH "../assets/fonts/font_film.ttf"
#define FONT_SIZE 40
#define LIST_PIONS_INIT {4,4,4,4,4,4,4,4,4,4,4,4}


SDL_Renderer* run_engine(void){
    if (!SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS) < 0) {
        fprintf(stderr, "Erreur d'initialisation: %s\n", SDL_GetError());
        return NULL;
    }
    if (TTF_Init() == -1){
        fprintf(stderr, "Erreur de lancement: %s", SDL_GetError());
        return NULL;
    }
    SDL_Window* fenetre;
     
    fenetre = SDL_CreateWindow("Game", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_ALWAYS_ON_TOP);
    if (!fenetre) {
        fprintf(stderr, "Erreur de création de la fenêtre et du renderer: %s\n", SDL_GetError());
        return NULL;
    }
    return fenetre;
}

TTF_Font* load_font(const char* font_path, int font_size){
    TTF_Font *police = TTF_OpenFont(font_path, font_size);
    if (!police){
        fprintf(stderr, "Erreur de chargement de la police: %s", SDL_GetError());
        return NULL;
    } 
    return police;
}

void stop_features(SDL_Renderer*ListRenderers[], int nbRenderers,SDL_Texture* ListTextures[],int nbTextures ,TTF_Font* ListFonts[], int nbFonts){
    // Pour fermer toutes les polices utilisées
    for (int i=0;i<nbFonts;i++){
        TTF_CloseFont(ListFonts[i]);
    }

    // Pour fermer toutes textures utilisées
    for (int i= 0; i<nbTextures; i++){
        SDL_DestroyTexture(ListTextures[i]);
    }

    //Pour détruire tous les renderers
    for (int i=0; i<nbRenderers;i++){
        SDL_DestroyRenderer(ListRenderers[i]);
    }
}

void stop_engine(SDL_Window*window){
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_Quit();
}
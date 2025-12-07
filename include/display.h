#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

//Afficher le score des joueurs dans le coin inférieur gauche de l'écran
void displayScore(SDL_Renderer * renderer, TTF_Font* police, int ScorePlayer1, int ScorePlayer2);


//Afficher le message de victoire au centre de l'écran
void displayVictory(SDL_Renderer * renderer, TTF_Font* police, int ScorePlayer1, int ScorePlayer2);


//Afficher le contenu des trous sur le plateau
void displayContainsOfHoles(int ListePions[12], SDL_Renderer * renderer, TTF_Font* police, int POS_TROUS[12][2] );

//Charger la texture de fond du plateau depuis un fichier image et le mettre dans renderer
SDL_Texture* loadPlateauBackground(SDL_Renderer * renderer, const char* filepath);


//Dessiner la texture de fond du plateau sur le renderer
void drawPlateauBackground(SDL_Renderer * renderer, SDL_Texture* plateauTexture);   

//Créer une texture de la surface du plateau de jeu
SDL_Texture* createSurfaceTexturePlateau(SDL_Renderer * renderer);

//Afficher tout avec un délai
void displayAllWithDelay(
    SDL_Renderer * renderer,
    SDL_Texture*plateauTexture, 
    TTF_Font* police,
    int ListePions[12],
    int POS_TROUS[12][2],
    int scorePlayer1, 
    int scorePlayer2, 
    int delayMs
);


#endif // DISPLAY_H
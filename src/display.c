#include "display.h"
#include <stdio.h>
#include <stdbool.h>
#include <SDL3/SDL.h> 
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include "outils.h"
#include "animation.h"




static void displayScorePlayer(SDL_Renderer*scoreRenderer, TTF_Font* police, int ScorePlayer1,bool VsAi, bool player1Turn){
    char tscorePlayer1[3];
    snprintf(tscorePlayer1, sizeof(tscorePlayer1), "%d", ScorePlayer1);

    char name[3];
    char namePlayer1[3];
    snprintf(name, sizeof(name), "%s", player1Turn ? "J1" : "J2");
    snprintf(namePlayer1, sizeof(namePlayer1), "%s", VsAi ? "AI" : name);


    SDL_Color grisFonce ={
        .a =255,
        .b = 0,
        .g = 30,
        .r = 51
    };

    SDL_Surface *SurfaceScore = TTF_RenderText_Blended(police, tscorePlayer1,sizeof(tscorePlayer1), grisFonce);
    if(!SurfaceScore){
        fprintf(stderr, "Erreur de création du texte: %s\n", SDL_GetError());
        return;
    }
    SDL_Surface *SurfaceName = TTF_RenderText_Blended(police, namePlayer1,sizeof(namePlayer1), grisFonce);
    if(!SurfaceName){
        fprintf(stderr, "Erreur de création du texte: %s\n", SDL_GetError());
        return;
    }

    SDL_Texture *TextureScore = SDL_CreateTextureFromSurface(scoreRenderer, SurfaceScore);
    if(!TextureScore){
        fprintf(stderr, "Erreur de création de la texture: %s\n", SDL_GetError());
        SDL_DestroySurface(SurfaceScore);
        return;
    }
    SDL_Texture *TextureName = SDL_CreateTextureFromSurface(scoreRenderer, SurfaceName);
    if(!TextureName){
        fprintf(stderr, "Erreur de création de la texture: %s\n", SDL_GetError());
        SDL_DestroySurface(SurfaceName);
        return;
    }


    SDL_FRect nameRect = {
        .x=(player1Turn)? 15+20:1165+20,
        .y= 250+20,
        .h = 40,
        .w = 60
    };
    SDL_FRect scoreRect = {
        .x=(player1Turn)? 15+20:1165+20,
        .y= 470+30,
        .h = 40,
        .w = 60
    };

    SDL_DestroySurface(SurfaceScore);
    SDL_DestroySurface(SurfaceName);

    SDL_RenderTexture(scoreRenderer, TextureName, NULL, &nameRect);
    SDL_RenderTexture (scoreRenderer, TextureScore, NULL, &scoreRect);

    SDL_DestroyTexture(TextureName);
    SDL_DestroyTexture(TextureScore);
}

void displayScores(SDL_Renderer* renderer, TTF_Font*police,bool VsAI, int scorePlayer1, int scorePlayer2){
    displayScorePlayer(renderer, police, scorePlayer1,VsAI,true);
    displayScorePlayer(renderer, police, scorePlayer2,false,false);
};





void displayContainsOfHoles(int ListePions[12], SDL_Renderer * renderer, TTF_Font* police, int POS_TROUS[12][2], int POS_RECT[12][2]){
    for (int i = 0; i < 12; i++) {
        char pionText[3];
        snprintf(pionText, sizeof(pionText), "%d", ListePions[i]);
        
        SDL_Color Noire ={
            .a =255,
            .b = 0,
            .g = 30,
            .r = 50
        };
        SDL_Surface *SurfaceText = TTF_RenderText_Blended(police, pionText, sizeof(pionText), Noire);
        if(!SurfaceText){
            fprintf(stderr, "Erreur de création du texte: %s\n", SDL_GetError());
            continue;
        }   
        SDL_Texture *TextureText = SDL_CreateTextureFromSurface(renderer, SurfaceText);
        if(!TextureText){
            fprintf(stderr, "Erreur de création de la texture: %s\n", SDL_GetError());
            SDL_DestroySurface(SurfaceText);
            continue;
        }
        SDL_DestroySurface(SurfaceText);
        SDL_FRect r1 = { .x = POS_RECT[i][0] +60,
                        .y = POS_RECT[i][1] +20,
                        .h = 30,
                        .w = 40
                    };

        SDL_RenderTexture(renderer,TextureText, NULL, &r1);
        SDL_DestroyTexture(TextureText);
    }
}

void displayPlateauWithDelay(
    SDL_Renderer * rendererPlateau,
    SDL_Texture*plateauTexture,
    TTF_Font* policePlateau,
    Button*ListButtons[],
    SDL_Texture*graineTexture, 
    int nbButtons,
    int POS_TROUS[12][2],
    int POS_RECT[12][2],
    int ListePions[12],
    int scorePlayer1,
    int scorePlayer2,
    bool VsAI,
    int delayMs
    ){
    SDL_RenderClear(rendererPlateau);
    SDL_RenderTexture(rendererPlateau, plateauTexture, NULL,NULL);

    for (int btn=0; btn<nbButtons; btn++){
                 renderbutton(rendererPlateau, ListButtons[btn]);
            } 
    //SDL_RenderTexture(rendererPlateau,plateauTexture,NULL,NULL);
    displayScores(rendererPlateau, policePlateau,VsAI, scorePlayer1,scorePlayer2);
    drawAllThePlaterSeeds(rendererPlateau, graineTexture, POS_TROUS, ListePions);
    displayContainsOfHoles(ListePions, rendererPlateau, policePlateau, POS_TROUS,POS_RECT);
    
    SDL_RenderPresent(rendererPlateau);
    SDL_Delay(delayMs); 
}

/*=========================================== END ================================================*/

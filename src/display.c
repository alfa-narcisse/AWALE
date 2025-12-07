#include "display.h"
#include <stdio.h>
#include <SDL3/SDL.h> 
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

void displayScore(SDL_Renderer * renderer, TTF_Font* police, int ScorePlayer1, int ScorePlayer2){
    char scoreText[50];
    snprintf(scoreText, sizeof(scoreText), "Player I: %d  -  Player II: %d", ScorePlayer1, ScorePlayer2);
    
    SDL_Color Noire ={
        .a =255,
        .b = 45,
        .g = 100,
        .r = 100
    };
    SDL_Surface *SurfaceScore = TTF_RenderText_Blended(police, scoreText,sizeof(scoreText), Noire);
    if(!SurfaceScore){
        fprintf(stderr, "Erreur de création du texte: %s\n", SDL_GetError());
        return;
    }   
    SDL_Texture *TextureScore = SDL_CreateTextureFromSurface(renderer, SurfaceScore);
    if(!TextureScore){
        fprintf(stderr, "Erreur de création de la texture: %s\n", SDL_GetError());
        SDL_DestroySurface(SurfaceScore);
        return;
    }
    int renderer_w = 0, renderer_h = 0;
    SDL_GetCurrentRenderOutputSize(renderer, &renderer_w, &renderer_h); // dynamic renderer/window size
    SDL_FRect ScoreRect = {
        10, // left margin
        renderer_h - SurfaceScore->h - 10,// bottom-left with 10px margin
        SurfaceScore->w,// width
        SurfaceScore->h // height
    };

    SDL_DestroySurface(SurfaceScore);
    SDL_RenderTexture   (renderer, TextureScore, NULL, &ScoreRect);
    SDL_DestroyTexture(TextureScore);
}

void displayVictory(SDL_Renderer * renderer, TTF_Font* police, int ScorePlayer1, int ScorePlayer2){
    const char* victoryMessage = (ScorePlayer1 > ScorePlayer2) ? "PLAYER I WINS!" : "PLAYER II WINS!";
    
    SDL_Color Noire ={
        .a =255,
        .b = 45,
        .g = 100,
        .r = 100
    };
    SDL_Surface *SurfaceVictory = TTF_RenderText_Blended(police, victoryMessage, sizeof(victoryMessage), Noire);
    if(!SurfaceVictory){
        fprintf(stderr, "Erreur de création du texte: %s\n", SDL_GetError());
        return;
    }   
    SDL_Texture *TextureVictory = SDL_CreateTextureFromSurface(renderer, SurfaceVictory);
    if(!TextureVictory){
        fprintf(stderr, "Erreur de création de la texture: %s\n", SDL_GetError());
        SDL_DestroySurface(SurfaceVictory);
        return;
    }
    int renderer_w = 0, renderer_h = 0;
    SDL_GetCurrentRenderOutputSize(renderer, &renderer_w, &renderer_h); // dynamic renderer/window size
    SDL_FRect VictoryRect = {
        (renderer_w - SurfaceVictory->w) / 2.0f, // centered horizontally
        (renderer_h - SurfaceVictory->h) / 2.0f, // centered vertically
        SurfaceVictory->w,// width
        SurfaceVictory->h // height
    };

    SDL_DestroySurface(SurfaceVictory);
    SDL_RenderTexture   (renderer, TextureVictory, NULL, &VictoryRect);
    SDL_DestroyTexture(TextureVictory);
}


void displayContainsOfHoles(int ListePions[12], SDL_Renderer * renderer, TTF_Font* police, int POS_TROUS[12][2]){
    for (int i = 0; i < 12; i++) {
        char pionText[2];
        snprintf(pionText, sizeof(pionText), "%d", ListePions[i]);
        
        SDL_Color Noire ={
            .a =255,
            .b = 45,
            .g = 100,
            .r = 100
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

        SDL_FRect dstRect;
        dstRect.w = 50; // Largeur fixe pour le texte
        dstRect.h = 50; // Hauteur fixe pour le texte
        dstRect.x = POS_TROUS[i][0] - dstRect.w / 2; // Centrer le texte
        dstRect.y = POS_TROUS[i][1] - dstRect.h / 2; // Centrer le texte
    
        // Dessiner la texture du nombre
        SDL_RenderTexture(renderer, TextureText, NULL, &dstRect);
        SDL_DestroyTexture(TextureText);
    }
}

SDL_Texture* loadPlateauBackground(SDL_Renderer * renderer, const char* filepath){
    SDL_Surface* surface = IMG_Load(filepath);
    if (!surface){
        fprintf(stderr, "Erreur de chargement de la surface: %s\n", SDL_GetError());
        return NULL;
    } 
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    return texture;
}

void drawPlateauBackground(SDL_Renderer * renderer, SDL_Texture* plateauTexture){
    if (!plateauTexture) return;
    
    int rw = 0, rh = 0;
    SDL_GetCurrentRenderOutputSize(renderer, &rw, &rh); // dynamic renderer/window size

    SDL_FRect dstRect = {
        .x = 0.0f,
        .y = 0.0f,
        .w = (float)rw,
        .h = (float)rh,
    };

    SDL_RenderTexture(renderer, plateauTexture, NULL, &dstRect);
}


// Plateau de jeu (Pour essai)
static void drawCercle(int x, int y, int R, SDL_Surface* surface) {
    if (!surface) return;
    
    SDL_LockSurface(surface);
    
    int pixelsPerLine = surface->pitch / sizeof(Uint32);
    Uint32* pixels = (Uint32*)surface->pixels;
    
    // Calculer les limites
    int minX = SDL_max(x - R, 0);
    int maxX = SDL_min(x + R, surface->w - 1);
    int minY = SDL_max(y - R, 0);
    int maxY = SDL_min(y + R, surface->h - 1);
    
    // Créer la couleur
    Uint32 couleurBlanche = SDL_MapRGBA(SDL_GetPixelFormatDetails(surface->format), NULL, 255, 255, 255, 255);
    
    // Dessiner
    for (int i = minX; i <= maxX; i++) {
        for (int j = minY; j <= maxY; j++) {
            int dx = i - x;
            int dy = j - y;
            if (dx * dx + dy * dy <= R * R) {
                pixels[j * pixelsPerLine + i] = couleurBlanche;
            }
        }
    }
    
    SDL_UnlockSurface(surface);
}

void displayTitleOfGame(SDL_Renderer * renderer, TTF_Font* police){
    const char* welcomeMessage = "AWALE";
    SDL_Color Noire ={
        .a =255,
        .b = 45,
        .g = 100,
        .r = 100
    };
    SDL_Surface *SurfaceText = TTF_RenderText_Blended(police, welcomeMessage,sizeof(welcomeMessage), Noire);
    if(!SurfaceText){
        fprintf(stderr, "Erreur de création du texte: %s\n", SDL_GetError());
        return;
    } 
 
    
    SDL_Texture*pTextureText = SDL_CreateTextureFromSurface(renderer,SurfaceText);
    if (!pTextureText){
        fprintf(stderr, "Erreur de création de la texture du texte: %s\n", SDL_GetError());
        SDL_DestroySurface(SurfaceText);
        return;
    }
     SDL_FRect dstTextRect;
    dstTextRect.x = 1475 / 2 - SurfaceText->w / 2;
    dstTextRect.y = 700;
    dstTextRect.w = SurfaceText->w;
    dstTextRect.h = SurfaceText->h;
    
    SDL_DestroySurface(SurfaceText);
    SDL_RenderTexture(renderer, pTextureText, NULL, &dstTextRect);
    SDL_DestroyTexture(pTextureText);  
}


SDL_Texture* createSurfaceTexturePlateau(SDL_Renderer * renderer){
    SDL_Surface* surface = SDL_CreateSurface(1375+50,600+50,SDL_PIXELFORMAT_RGBA32); 
    if (!surface){
        fprintf(stderr, "Erreur de création de la surface: %s\n", SDL_GetError());
        return NULL;
    } 
    Uint32 blanc = SDL_MapRGBA(SDL_GetPixelFormatDetails(surface->format),NULL,120,120,200, 255);
    SDL_FillSurfaceRect(surface, &(SDL_Rect){50,50,1375,600},blanc);
    
    //Dessiner les trous
    for (int i = 0; i<6;i++){
        drawCercle(225*i+125+50,125+50,100, surface);
        drawCercle(225*i+125+50, 450+50,100, surface);
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
    return texture;
}


void displayAllWithDelay(
    SDL_Renderer * renderer,
    SDL_Texture*plateauTexture, 
    TTF_Font* police,
    int ListePions[12],
    int POS_TROUS[12][2],
    int scorePlayer1,
    int scorePlayer2,
    int delayMs){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    drawPlateauBackground(renderer, plateauTexture);
    displayContainsOfHoles(ListePions, renderer, police, POS_TROUS);
    displayTitleOfGame(renderer, police);
    displayScore(renderer, police, scorePlayer1, scorePlayer2);
    SDL_RenderPresent(renderer);
    SDL_Delay(delayMs); 
}


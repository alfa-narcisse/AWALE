#ifndef ENGINE_H
#define ENGINE_H
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

// Initialiser le moteur SDL, créer la fenêtre et le renderer
SDL_Window* run_engine(void);

// Charger une police de caractères depuis un fichier
TTF_Font* load_font(const char* font_path, int font_size);

// Arrêter le moteur SDL et libérer les ressources
void stop_features(SDL_Renderer*ListRenderers[], int nbRenderers,SDL_Texture*ListTextures[],int nbTextures, TTF_Font* ListFonts[], int nbFonts);
#endif // ENGINE_H
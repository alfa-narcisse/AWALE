#include "umbrella.h"



int main(int argc, char* argv[]){
    
    if (!SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) || !TTF_Init()){
        fprintf(stderr, "Erreur: %s", SDL_GetError());
    }
    
    SDL_Window *win=SDL_CreateWindow("Menu",1280,720,0);
    if (!win){
        fprintf(stderr, "Erreur: %s", SDL_GetError());
    }
   
    DeviceID* deviceId = InitAudioDevice();
    AudioStreamInstance* bg_audioStreamInstance = LoadWAV("../assets/audio/ground_sound.wav", deviceId);
    SDL_SetAudioStreamGain(bg_audioStreamInstance->stream, 0.04f);
    
    int ListePions[12] = {4,4,4,4,4,4,4,4,4,4,4,4};
    AfficheMenu(win, ListePions,bg_audioStreamInstance);


    CleanUpAudioStreamInstance(bg_audioStreamInstance);
    CleanUpDevice(deviceId);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

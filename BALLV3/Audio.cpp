#include "Audio.h"
#include <iostream>

Audio::Audio() : music(nullptr) {}

Audio::~Audio() {
    cleanup();
}

bool Audio::initialize() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cout << "audio no good SDL Audio: " << SDL_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "mixer no good SDL_mixer: " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}

bool Audio::loadMp3(const std::string& filePath) {
    music = Mix_LoadMUS(filePath.c_str());
    if (!music) {
        std::cout << " MP3 file no good : " << Mix_GetError() << std::endl;
        return false;
    }

    return true;
}

void Audio::play() {
    if (music) {
        //hitsound
        Mix_PlayMusic(music, 1);
    }
    else {
        std::cout << "no music xddxdxd" << std::endl;
    }
}

void Audio::cleanup() {
    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;
    }

    Mix_CloseAudio();
    SDL_Quit();
}

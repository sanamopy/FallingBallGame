#include "Audio.h"
#include <iostream>

Audio::Audio() : hitSound(nullptr) {}

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
    hitSound = Mix_LoadMUS(filePath.c_str());
    deathSound = Mix_LoadMUS(filePath.c_str());
    if (!hitSound) {
        std::cout << " MP3/1 file no good : " << Mix_GetError() << std::endl;
        return false;
    }
    if (!deathSound)
    {
        std::cout << "MP3/2 file no good: " << Mix_GetError() << std::endl;
        return false;
    }


    return true;
}

void Audio::play() {
    if (hitSound) {
        //hitsound
        Mix_PlayMusic(hitSound, 1);
    }
    if (deathSound) {
        Mix_PlayMusic(deathSound, 1);
    }
    else {
        std::cout << "no music xddxdxd" << std::endl;
    }
}

void Audio::cleanup() {
    if (hitSound) {
        Mix_FreeMusic(hitSound);
        hitSound = nullptr;
    }
    if (deathSound) {
        Mix_FreeMusic(deathSound);
        deathSound = nullptr;
    }

    Mix_CloseAudio();
    SDL_Quit();
}

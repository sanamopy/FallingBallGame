#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class Audio {
public:
    Audio();
    ~Audio();

    bool initialize();
    bool loadMp3(const std::string& filePath);
    void play();
    void cleanup();

private:
    Mix_Music* hitSound;
    Mix_Music* deathSound;
};

#endif // AUDIO_H

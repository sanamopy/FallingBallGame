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
    bool loadMp3(const std::string& hitFilePath, const std::string& deathFilePath, const std::string& levelUpFilePath);
    void playHitSound();
    void playDeathSound();
    void playLevelUpSound();
    void cleanup();

private:
    Mix_Chunk* hitSound;     // Sound effect for "hit"
    Mix_Chunk* deathSound;   // Sound effect for "death"
    Mix_Chunk* levelUpSound; // Sound effect for "level-up"
};

#endif // AUDIO_H

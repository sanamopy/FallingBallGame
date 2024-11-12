#pragma once
#ifndef FONTMANAGER_H
#define FONTMANAGER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <map>
#include "Player.h"
class FontManager {
public:
    static FontManager& Instance();

    bool LoadFont(const std::string& fontID, const std::string& path, int fontSize);
    void RenderText(const std::string& fontID, const std::string& text, SDL_Color color, int x, int y, SDL_Renderer* renderer);
    void RenderScore(const std::string& fontID, SDL_Color color, int x, int y, SDL_Renderer* renderer, Player& player);
    void CleanUp();

private:
    FontManager() = default;
    ~FontManager() = default;
    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;

    std::map<std::string, TTF_Font*> fonts;
};

#endif // FONTMANAGER_H

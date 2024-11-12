#include "FontManager.h"
#include <iostream>

FontManager& FontManager::Instance() {
    static FontManager instance;
    return instance;
}

bool FontManager::LoadFont(const std::string& fontID, const std::string& path, int fontSize) {
    TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);
    if (!font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }
    fonts[fontID] = font;
    return true;
}

void FontManager::RenderText(const std::string& fontID, const std::string& text, SDL_Color color, int x, int y, SDL_Renderer* renderer) {
    TTF_Font* font = fonts[fontID];
    if (!font) {
        std::cout << "Font ID not good: " << fontID << std::endl;
        return;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!textSurface) {
        std::cout << "text rendering not good TTF_Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    if (!textTexture) {
        std::cout << "texture from rendered text not good SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_DestroyTexture(textTexture);
}

void FontManager::RenderScore(const std::string& fontID, SDL_Color color, int x, int y, SDL_Renderer* renderer, Player& player) {
    int score = player.getScore();
    if (score != lastScore) {
        lastScore = score;
        if (cachedScoreTexture) {
            SDL_DestroyTexture(cachedScoreTexture);
            cachedScoreTexture = nullptr;
        }

        std::string scoreText = "Score: " + std::to_string(score);
        TTF_Font* font = fonts[fontID];
        if (!font) {
            std::cout << "Font ID not good: " << fontID << std::endl;
            return;
        }

        SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), color);
        if (!textSurface) {
            std::cout << "text rendering not good TTF_Error: " << TTF_GetError() << std::endl;
            return;
        }

        cachedScoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_FreeSurface(textSurface);
        if (!cachedScoreTexture) {
            std::cout << "texture from rendered text not good SDL_Error: " << SDL_GetError() << std::endl;
            return;
        }
    }

    int textWidth, textHeight;
    SDL_QueryTexture(cachedScoreTexture, nullptr, nullptr, &textWidth, &textHeight);
    SDL_Rect textRect = { x, y, textWidth, textHeight };

    SDL_RenderCopy(renderer, cachedScoreTexture, nullptr, &textRect);
}


void FontManager::CleanUp() {
    for (auto& font : fonts) {
        TTF_CloseFont(font.second);
    }
    fonts.clear();

    if (cachedScoreTexture) {
        SDL_DestroyTexture(cachedScoreTexture);
        cachedScoreTexture = nullptr;
    }
}


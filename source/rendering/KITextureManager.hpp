#pragma once

#include <SDL2/SDL.h>
#include <vector>

class KITextureManager
{
public:
    KITextureManager() = default;
    ~KITextureManager();
    SDL_Texture* getTexture(size_t textureID) const;
    size_t addTexture(SDL_Texture* texture);
public:
    std::vector<SDL_Texture*> textures;
};
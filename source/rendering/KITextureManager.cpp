#include "KITextureManager.hpp"

KITextureManager::~KITextureManager()
{
    for (SDL_Texture* texture : textures) {
        SDL_DestroyTexture(texture);
    }
}

SDL_Texture* KITextureManager::getTexture(size_t textureID) const
{
    return textures[textureID];
}

size_t KITextureManager::addTexture(SDL_Texture* texture)
{
    textures.push_back(texture);
    return textures.size() - 1;
}

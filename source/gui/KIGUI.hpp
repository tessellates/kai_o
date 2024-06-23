#pragma once

#include "KIDisplay.hpp"
#include "BlinkMenu.hpp"
#include <SDL2/SDL.h>

class KIGUI
{
public:
    KIGUI() = default;
    ~KIGUI() = default;
    void render(bool isMenuMode);

    KIDisplay kid;
    BlinkMenu menu;
    SDL_Texture* texture;
};
#pragma once

#include "AppClock.hpp"
#include "Singleton.hpp"
#include "FrameRateCounter.hpp"

#include <vector>
#include <SDL2/SDL.h>
#include "imgui.h"


// remove
#include "KITextureManager.hpp"
//
class Engine;
class KIGUI;

class KIApplication : public Singleton<KIApplication>
{
   friend class Singleton<KIApplication>; // Grant base access to constructor.
public:
    // boiler-plate singleton
    KIApplication(KIApplication &other) = delete;
    void operator=(const KIApplication &) = delete;

    int run();
    void init(bool test = true);
    void updateDisplay();
    void toggleFullscreen();
    void changeWindow();

    static bool isFullscreen;
    static int currentResolutionIndex;
    static float deltaTime;
    static bool showFrameRate;

    static SDL_Renderer* renderer;
    static SDL_Rect display;
    SDL_Event event;

    std::vector<std::pair<int,int>> resolutions;

private:
    KIApplication();
    ~KIApplication();
public:
    void loop();
    
    Engine* engine = nullptr;
    KIGUI* gui = nullptr;

    SDL_Window* window = nullptr;
    ImGuiIO* io;

    bool isRunning = true;
    bool isMenuMode = false;
    bool isInit = false;

    AppClock clock;
    FrameRateCounter frc;

    // remove
    KITextureManager kt;
    bool flip = true;
};

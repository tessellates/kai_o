#pragma once

#include "imgui.h"

class KIDisplay
{
public:
    KIDisplay() = default;
    ~KIDisplay() = default;
    void init();
    void execute();
    void render();
    void reset();

    int offset = 60;
    ImVec2 size = {864, 576};
    ImGuiWindowFlags flags = (ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
};



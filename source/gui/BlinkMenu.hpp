#pragma once

#include "imgui.h"

#include <vector>

class BlinkMenu
{
public:
    BlinkMenu() = default;
    virtual ~BlinkMenu() = default;
    void addResolutions(const std::vector<std::pair<int,int>>&);
    void init();
    void run();

    std::vector<std::string> validResolutions;
};

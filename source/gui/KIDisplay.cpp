
#include "Utilities.hpp"
#include "KIDisplay.hpp"


void KIDisplay::init()
{
}

void KIDisplay::render()
{
    // Get the display size (example code, replace with actual display size retrieval)
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;

    offset = 60 * (160 * size.y/76)/displaySize.y;
    if (displaySize.y <= size.y)
        offset = 0;

    // Calculate the centered position
    ImVec2 pos = ImVec2((displaySize.x - size.x) / 2.0f, (displaySize.y - size.y - offset) / 2.0f);

    // Set the window position and size
    ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);

    // Begin the window
    ImGui::Begin("Texture", nullptr, flags);
    ImGui::End();
}

void KIDisplay::execute()
{
    init();
    ImGui::SetCursorPos({0,0});
}

void KIDisplay::reset()
{
}

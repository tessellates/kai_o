#include "BlinkMenu.hpp"
#include "KIApplication.hpp"
#include "SDLUserEvents.hpp"

#include <vector>

void BlinkMenu::run()
{
    // Set the background alpha of the next window (this is optional)
    ImGui::SetNextWindowBgAlpha(1); // Adjust the alpha as needed

    // Get the display size (example code, replace with actual display size retrieval)
    ImVec2 displaySize = ImGui::GetIO().DisplaySize;

    ImVec2 size = {864, 576};
    int offset = 60 * (160 * size.y/76)/displaySize.y;
    if (displaySize.y <= size.y)
        offset = 0;

    //Calculate the centered position
    //ImVec2 size = displaySize - ImVec2{50, 50};
        // Calculate the centered position
    ImVec2 pos = ImVec2((displaySize.x - size.x) / 2.0f, (displaySize.y - size.y - offset) / 2.0f);

    // Set the window position and size
    ImGui::SetNextWindowPos(pos, ImGuiCond_Always);
    ImGui::SetNextWindowSize(size, ImGuiCond_Always);
    //ImVec2 pos = ImVec2((displaySize.x - size.x) / 2.0f, (displaySize.y - size.y) / 2.0f);*


    // Begin the settings window
    ImGui::Begin("Settings", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    // Title for the settings category
    ImGui::Text("Game Settings");

    // Fullscreen toggle
    if (ImGui::Checkbox("Fullscreen", &KIApplication::isFullscreen)) {
        SDL_Event event;
        SDL_zero(event); // Initialize the event to zero
        event.type = KI_FULLSCREEN_TOGGLE;
        SDL_PushEvent(&event);
    }

    static int currentResolution = 0; // Variable to store the current selection, change it as per your needs or application state
    if (!KIApplication::isFullscreen)
    {
        if (ImGui::BeginCombo("Resolution", validResolutions[KIApplication::currentResolutionIndex].c_str())) {
            for (int i = 0; i < validResolutions.size(); i++) {
                bool isSelected = (KIApplication::currentResolutionIndex == i);
                if (ImGui::Selectable(validResolutions[i].c_str(), isSelected)) {
                    KIApplication::currentResolutionIndex = i; // Update the current resolution on selection
                    SDL_Event event;
                    SDL_zero(event); // Initialize the event to zero
                    event.type = KI_RESOLUTION_CHANGE;
                    SDL_PushEvent(&event);

                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }        
    }
    // Fullscreen toggle
    if (ImGui::Checkbox("Framerate", &KIApplication::showFrameRate)) {
    }
    ImGui::End();
}

void BlinkMenu::init() {}

void BlinkMenu::addResolutions(const std::vector<std::pair<int,int>>& sizes)
{
    validResolutions = std::vector<std::string>();
    for (const auto& res : sizes) 
    {
        validResolutions.push_back(std::to_string(res.first) + "x" + std::to_string(res.second));
    }
}

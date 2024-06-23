#include "KIGUI.hpp"
#include "KIApplication.hpp"
#include "BlinkMenu.hpp"

#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

void KIGUI::render(bool isMenuMode)
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();  
    ImGui::NewFrame();


    int windowWidth, windowHeight;
    SDL_GetWindowSize(KIApplication::instance()->window, &windowWidth, &windowHeight);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)windowWidth, (float)windowHeight));
    ImGui::Begin("Main Frame", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    if (texture) {
        int th = 576;
        int tw = th*1.5;
        int offset = 6;
        int basew = 114;
        int baseh = 76;
        ImVec2 displaySize = ImGui::GetIO().DisplaySize;
        int offset2 = 60 * (160 * th/baseh)/displaySize.y;
        if (displaySize.y <= th)
            offset2 = 0;

        int absoffset = offset * th/baseh - offset2;
        int width, height;
        height = 160 * th/baseh;
        width = height*1.6;
        //SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
        ImGui::SetCursorPos({float(windowWidth - width)/2,float(windowHeight - height + absoffset)/2 });
        //ImGui::SetCursorPos({0,float(windowHeight - height)/2});
        ImGui::Image(texture, ImVec2(width, height));
    }
    kid.render();
    if (isMenuMode)
    {
        menu.run();
    }
    ImGui::End(); // End the main frame
    ImGui::Render();
    SDL_RenderSetScale(KIApplication::renderer, ImGui::GetIO().DisplayFramebufferScale.x, ImGui::GetIO().DisplayFramebufferScale.y);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), KIApplication::renderer);
}
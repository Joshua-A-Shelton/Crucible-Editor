#include <crucible/Crucible.h>
#include "Editor.h"
#include "dear-imgui/imgui_impl_sdl3.h"
#include "dear-imgui/imgui_impl_slag.h"
int main()
{
    bool debug = false;
#ifndef NDEBUG
    debug = true;
#endif
    if(crucible::Crucible::initialize(crucible::Crucible::RenderingBackend::VULKAN,debug))
    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multiple Viewports


        auto flags = SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE;
        if(slag::SlagLib::usingBackEnd() == slag::VULKAN)
        {
            flags|= SDL_WINDOW_VULKAN;
        }
        auto window = SDL_CreateWindow("Crucible Editor",500,800,flags);

        slag::SamplerBuilder sb;
        auto uiSampler = sb.newSampler();

        crucible::Editor editor(uiSampler);
        editor.run();

        delete uiSampler;
        SDL_DestroyWindow(window);
    }
    ImGui::DestroyContext();
    crucible::Crucible::cleanup();
    return 0;
}
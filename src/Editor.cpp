#include "Editor.h"
#include "dear-imgui/imgui_impl_sdl3.h"
#include "dear-imgui/imgui_impl_slag.h"

using namespace crucible;
using namespace slag;
namespace crucible
{
    void* extractNativeWindowHandle(ImGuiViewport* viewport)
    {
#ifdef _WIN32
        return viewport->PlatformHandleRaw;

#elif __linux
        //SDL backend stores window not as SDL_Window*, but a uint32 id for some reason
        SDL_Window* window = SDL_GetWindowFromID((intptr_t)(viewport->PlatformHandle));
        const char* driverName = SDL_GetCurrentVideoDriver();
        auto properties = SDL_GetWindowProperties(window);
        if (strcmp(driverName, "wayland") == 0)
        {
            return SDL_GetPointerProperty(properties,SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, nullptr);
        }
        else
        {
            return reinterpret_cast<void*>(SDL_GetNumberProperty(properties,SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0));
        }
#else
        return nullptr;
#endif
    }

    Editor::Editor(slag::Sampler* UiSampler):Game("Crucible Editor","crucible.png", nullptr)
    {
        ImGui_ImplSDL3_InitForOther(_window);


        slag::PlatformData platformData{};

        auto properties = SDL_GetWindowProperties(_window);
#ifdef _WIN32
        platformData.platform = slag::PlatformData::WIN_32;
        platformData.data.win32.hwnd = SDL_GetPointerProperty(properties,SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);
        platformData.data.win32.hinstance = SDL_GetPointerProperty(properties,SDL_PROP_WINDOW_WIN32_INSTANCE_POINTER, nullptr);
#else
        const char* driverName = SDL_GetCurrentVideoDriver();
        if (strcmp(driverName, "wayland") == 0)
        {
            platformData.platform = slag::PlatformData::WAYLAND;
            platformData.data.wayland.surface = SDL_GetPointerProperty(properties,SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, nullptr);
            platformData.data.wayland.display = SDL_GetPointerProperty(properties,SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, nullptr);
        }
        else
        {
            platformData.platform = slag::PlatformData::X11;
            platformData.data.x11.display = SDL_GetPointerProperty(properties,SDL_PROP_WINDOW_X11_DISPLAY_POINTER, nullptr);
            platformData.data.x11.window = reinterpret_cast<void*>(SDL_GetNumberProperty(properties,SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0));
        }
#endif

        ImGui_ImplSlag_Init(_swapChain,platformData,extractNativeWindowHandle,UiSampler,Pixels::B8G8R8A8_UNORM_SRGB);
    }

    Editor::~Editor()
    {
        ImGui_ImplSlag_Shutdown();
        ImGui_ImplSDL3_Shutdown();
    }

    Editor& Editor::operator=(Editor&& from)
    {
        move(from);
        return *this;
    }

    void Editor::move(Editor& from)
    {
        Game::move(from);
    }

    void Editor::handleEvent(SDL_Event& event)
    {
        ImGui_ImplSDL3_ProcessEvent(&event);
        Game::handleEvent(event);
    }

    void Editor::update(double deltaTime)
    {
        Game::update(deltaTime);
    }

    void Editor::draw(slag::CommandBuffer* commandBuffer, slag::Texture* drawBuffer, slag::DescriptorPool* descriptorPool)
    {
        descriptorPool->reset();

        commandBuffer->begin();
        commandBuffer->bindDescriptorPool(descriptorPool);
        ImGui_ImplSlag_NewFrame(descriptorPool);
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        commandBuffer->setViewPort(0,0,static_cast<float>(drawBuffer->width()),static_cast<float>(drawBuffer->height()),1,0);
        commandBuffer->setScissors({{0,0},{drawBuffer->width(),drawBuffer->height()}});

        commandBuffer->insertBarrier(
                slag::ImageBarrier
                        {
                                .texture=drawBuffer,
                                .oldLayout=slag::Texture::UNDEFINED,
                                .newLayout=slag::Texture::RENDER_TARGET,
                                .accessBefore=slag::BarrierAccessFlags::NONE,
                                .accessAfter=slag::BarrierAccessFlags::SHADER_WRITE,
                                .syncBefore=slag::PipelineStageFlags::NONE,
                                .syncAfter=slag::PipelineStageFlags::FRAGMENT_SHADER
                        });

        slag::Attachment attachment{.texture=drawBuffer,.layout=slag::Texture::RENDER_TARGET,.clearOnLoad=true,.clear={.color={0.0f,0.0f,0.0f,1.0f}}};
        commandBuffer->beginRendering(&attachment,1, nullptr,{.offset={0,0},.extent={drawBuffer->width(),drawBuffer->height()}});

        ImGui::ShowDemoWindow();

        ImGui::Render();
        ImGui_ImplSlag_RenderDrawData(ImGui::GetDrawData(),commandBuffer);
        commandBuffer->endRendering();
        commandBuffer->insertBarrier(
                slag::ImageBarrier
                        {
                                .texture=drawBuffer,
                                .oldLayout=slag::Texture::RENDER_TARGET,
                                .newLayout=slag::Texture::PRESENT,
                                .accessBefore=slag::BarrierAccessFlags::SHADER_WRITE,
                                .accessAfter=slag::BarrierAccessFlags::NONE,
                                .syncBefore=slag::PipelineStageFlags::FRAGMENT_SHADER,
                                .syncAfter=slag::PipelineStageFlags::NONE
                        });
        commandBuffer->end();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }
    }
} // crucible
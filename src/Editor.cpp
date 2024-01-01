#include <iostream>
#include "Editor.h"

#include "Graphics/DearImGUI/imgui_impl_slag.h"
#include "backends/imgui_impl_sdl2.h"
#include "Graphics/Fonts.h"
#include "Controls/MenuBar.h"
#include "Graphics/DearImGUI/ImGuiInterop.h"
#include "crucible/Scripting/ScriptingEngine.h"
#include <crucible/Scripting/GameWorld.h>


namespace crucible
{
    Editor* editorInstance = nullptr;

    void Editor::initialize(const char *gameName, const char *iconPath)
    {
        Game::initialize(gameName, iconPath);
        crucible::ScriptingEngine::loadManagedDll("Crucible-Editor.dll");
        auto inspectorType = crucible::ScriptingEngine::getManagedType("CrucibleEditor.GUI.ProgramInterface, Crucible-Editor");
        drawInterface = inspectorType.getFunction<void(*)()>("DrawInterface");
        auto mainViewportType = ScriptingEngine::getManagedType("CrucibleEditor.GUI.Widgets.MainViewport, Crucible-Editor");
        setSceneTexture = mainViewportType.getFunction<void(*)(slag::Texture*)>("SetSceneTexture");
        ScriptingEngine::registerUnmanagedFunction("CrucibleEditor.GUI.Widgets.MainViewport, Crucible-Editor", "_resizeMainViewportTextures_ptr", reinterpret_cast<void **>(resizeMainViewPortTexture));

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImFontConfig font_cfg;
        font_cfg.FontDataOwnedByAtlas = false;
        Title = io.Fonts->AddFontFromMemoryTTF(recharge_bd_ttf,recharge_bd_ttf_len,16,&font_cfg);
        Body = io.Fonts->AddFontFromMemoryTTF(recharge_bd_ttf,recharge_bd_ttf_len,14,&font_cfg);
        crucible::ImGuiInterop::registerInteropFunctions(Title,Body);

        ImGui_ImplSDL2_InitForOther(window());
        ImGui_ImplSlag_Init(swapchain()->imageFormat());

        editorInstance = this;

    }

    void Editor::setUpSwapchain(slag::SwapchainBuilder& builder)
    {
        Game::setUpSwapchain(builder);
        builder.addTextureResource("MainViewportColor",{slag::TextureResourceDescription::SizingMode::Absolute,500,500,slag::Pixels::R8G8B8A8_UNORM,slag::Texture::Usage::COLOR,true});
        builder.addTextureResource("MainViewportDepth",{slag::TextureResourceDescription::SizingMode::Absolute,500,500,slag::Pixels::D32_SFLOAT,slag::Texture::Usage::DEPTH,true});
        builder.addVertexBufferResource("ImGuiVerts",{15000,slag::Buffer::Usage::GPU});
        builder.addIndexBufferResource("ImGuiIndexes",{15000,slag::Buffer::Usage::GPU});
        builder.setDrawOnMinimized(true);
    }

    void Editor::processEvents()
    {
        SDL_Event e;

        // Events management
        while(SDL_PollEvent(&e))
        {
            if( e.type == SDL_QUIT )
            {
                running = false;
            }
            else if(e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                running = false;
            }
            else if(e.type == SDL_WINDOWEVENT && (e.window.event == SDL_WINDOWEVENT_RESIZED || e.window.event == SDL_WINDOWEVENT_MAXIMIZED || e.window.event == SDL_WINDOWEVENT_MINIMIZED) )
            {
                handleResize();
            }
            ImGui_ImplSDL2_ProcessEvent(&e); // Forward your event to backend

        }
    }

    void Editor::update(float deltaTime)
    {
        Game::update(deltaTime);
    }

    void Editor::render(slag::Frame *frame)
    {
        frame->begin();
        ImGui_ImplSlag_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGui::PushFont(Title);

        auto* commandBuffer = frame->getCommandBuffer();

        slag::Attachment scene[2];
        slag::Texture* sceneColor = frame->getTextureResource("MainViewportColor");
        slag::Texture* sceneDepth = frame->getTextureResource("MainViewportDepth");
        slag::Rectangle sceneView{{0,0},{sceneColor->width(),sceneColor->height()}};
        scene[0] = {.texture = sceneColor,.clearOnLoad = true, .clear{0.937,0.494,0.259,1}};
        scene[1] = {.texture = sceneDepth,.clearOnLoad = true};
        slag::ImageMemoryBarrier startSceneimageMemoryBarrier;
        startSceneimageMemoryBarrier.texture = sceneColor;
        startSceneimageMemoryBarrier.oldLayout = slag::Texture::UNDEFINED;
        startSceneimageMemoryBarrier.newLayout = slag::Texture::RENDER_TARGET;
        startSceneimageMemoryBarrier.requireCachesFinish = slag::PipelineAccess::PipeLineAccessFlags::NONE;
        startSceneimageMemoryBarrier.usingCaches = slag::PipelineAccess::PipeLineAccessFlags::ACCESS_SHADER_READ_BIT;
        commandBuffer->insertBarriers(nullptr,0,&startSceneimageMemoryBarrier,1, nullptr,0,slag::PipelineStage::PipelineStageFlags::TOP,slag::PipelineStage::PipelineStageFlags::FRAGMENT_SHADER);

        slag::Rectangle rect{{0,0},{sceneColor->width(),sceneColor->height()}};
        commandBuffer->setViewport(rect);
        commandBuffer->setScissors(rect);

        commandBuffer->setTargetFramebuffer(sceneView,&scene[0],1,scene[1]);

        auto camera = GameWorld::getMainCamera();
        renderRegistry.draw(camera,frame);

        commandBuffer->endTargetFramebuffer();
        slag::ImageMemoryBarrier imageMemoryBarrier;
        imageMemoryBarrier.texture = sceneColor;
        imageMemoryBarrier.oldLayout = slag::Texture::RENDER_TARGET;
        imageMemoryBarrier.newLayout = slag::Texture::SHADER_RESOURCE;
        imageMemoryBarrier.requireCachesFinish = slag::PipelineAccess::PipeLineAccessFlags::ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        imageMemoryBarrier.usingCaches = slag::PipelineAccess::PipeLineAccessFlags::ACCESS_SHADER_READ_BIT;
        commandBuffer->insertBarriers(nullptr,0,&imageMemoryBarrier,1, nullptr,0,slag::PipelineStage::PipelineStageFlags::COLOR_ATTACHMENT_OUTPUT,slag::PipelineStage::PipelineStageFlags::FRAGMENT_SHADER);

        slag::Texture* backBuffer = frame->getBackBuffer();
        slag::Rectangle view{{0,0},{ backBuffer->width(),backBuffer->height()}};
        if(backBuffer->width() > 0 && backBuffer->height() > 0)
        {
            commandBuffer->setViewport(view);
            commandBuffer->setScissors(view);
        }
        slag::Attachment renderSurface{.texture = backBuffer, .clearOnLoad = true, .clear={0.5, 0.5, 0.5, 0.5}};
        commandBuffer->setTargetFramebuffer(view, &renderSurface, 1);


        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        //menuBar.show();
        setSceneTexture(sceneColor);
        drawInterface();

        ImGui::PopFont();
        ImGui::Render();
        ImGui_ImplSlag_RenderDrawData(ImGui::GetDrawData(),frame, nullptr);
        commandBuffer->endTargetFramebuffer();
        frame->end();

        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }

    void Editor::cleanup()
    {
        ImGui_ImplSlag_Shutdown();
        ImGui_ImplSDL2_Shutdown();

        ImGui::DestroyContext();
    }

    void Editor::resizeMainViewPortTexture(float width, float height)
    {
        if(editorInstance!= nullptr)
        {
            editorInstance->swapchain()->setResource("MainViewportColor",{slag::TextureResourceDescription::SizingMode::Absolute,width,height,slag::Pixels::R8G8B8A8_UNORM,slag::Texture::Usage::COLOR,true});
            editorInstance->swapchain()->setResource("MainViewportDepth",{slag::TextureResourceDescription::SizingMode::Absolute,width,height,slag::Pixels::D32_SFLOAT,slag::Texture::Usage::DEPTH,true});
        }
    }
} // crucible
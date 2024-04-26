#include <iostream>
#include "Editor.h"

#include "crucible/Scripting/ScriptingEngine.h"


namespace crucible
{

    void Editor::initialize(const char *gameName, const char *iconPath)
    {
        Game::initialize(gameName, iconPath);
    }

    void Editor::setUpSwapchain(slag::SwapchainBuilder& builder)
    {
        Game::setUpSwapchain(builder);
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

        }
    }

    void Editor::update(float deltaTime)
    {
        Game::update(deltaTime);
    }

    void Editor::render(slag::Frame *frame)
    {
        frame->begin();

        auto* commandBuffer = frame->getCommandBuffer();

        slag::Texture* backBuffer = frame->getBackBuffer();
        slag::Rectangle view{{0,0},{ backBuffer->width(),backBuffer->height()}};
        if(backBuffer->width() > 0 && backBuffer->height() > 0)
        {
            commandBuffer->setViewport(view);
            commandBuffer->setScissors(view);
        }
        slag::Attachment renderSurface{.texture = backBuffer, .clearOnLoad = true, .clear={0.5, 0.5, 0.5, 0.5}};
        commandBuffer->setTargetFramebuffer(view, &renderSurface, 1);

        commandBuffer->endTargetFramebuffer();
        frame->end();
    }

    void Editor::cleanup()
    {
    }



} // crucible
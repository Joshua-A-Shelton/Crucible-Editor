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
        slag::FrameGraphBuilder fgb;
        slag::GraphicsPass gp("basic_pass",slag::PipelineStage::PipelineStageFlags::ALL_GRAPHICS);

        gp.addGlobalTexture("output",slag::Texture::Usage::COLOR,slag::Texture::Layout::RENDER_TARGET, slag::PipelineAccess::PipeLineAccessFlags::ACCESS_COLOR_ATTACHMENT_WRITE_BIT);
        gp.setCallback([](slag::CommandBuffer* commandBuffer, slag::FrameResourceDictionary& resources, void* extra)
        {
            slag::Texture* backBuffer = resources.getTexture("output");
            slag::Rectangle view{{0,0},{ backBuffer->width(),backBuffer->height()}};
            if(backBuffer->width() > 0 && backBuffer->height() > 0)
            {
                commandBuffer->setViewport(view);
                commandBuffer->setScissors(view);
            }
            slag::Attachment renderSurface{.texture = backBuffer, .clearOnLoad = true, .clear={0.5, 0.5, 0.5, 0.5}};
            commandBuffer->setTargetFramebuffer(view, &renderSurface, 1);

            commandBuffer->endTargetFramebuffer();
        });
        fgb.addPass(gp);

        slag::GraphicsPass presentPass("present",slag::PipelineStage::BOTTOM);
        presentPass.addGlobalTexture("output",slag::Texture::COLOR,slag::Texture::Layout::PRESENT,slag::PipelineAccess::PipeLineAccessFlags::NONE);
        presentPass.setCallback([](slag::CommandBuffer* commandBuffer, slag::FrameResourceDictionary& resources, void* extra)
        {
            //std::cout<< "made presentable"<< std::endl;
        });
        fgb.addPass(presentPass);


        auto* commandBuffer = frame->getCommandBuffer();
        auto fg = fgb.compile();
        fg.setOutputTexture(frame->getBackBuffer());
        fg.execute(commandBuffer);


        frame->end();
    }

    void Editor::cleanup()
    {
    }



} // crucible
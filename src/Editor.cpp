#include <iostream>
#include "Editor.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "crucible/Scripting/ScriptingEngine.h"
#include "crucible/Graphics/Shaders/ShaderLibrary.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>

namespace crucible
{

    std::unordered_set<Editor*> OPEN_EDITORS;
    bool PROCESS_EDITORS = true;
    std::mutex EDITORS_MUTEX;
    std::thread* RENDER_THREAD = nullptr;
    float rotation = 0;

    slag::ComputeShader* compShader = nullptr;// slag::ComputeShader::create("Graphics/DefaultShaders/test.comp.spv");


    Editor::Editor(void *nativeHandle) : Game(nativeHandle)
    {
        setupResources("","");
    }

    void Editor::initialize(const char *gameName, const char *iconPath)
    {
        Game::initialize(gameName, iconPath);
        char colors[4] = {static_cast<char>(255),0,0,static_cast<char>(255)};
        _defaultTexture = slag::Texture::create("Crucible.png");//slag::Texture::create(1,1,slag::Pixels::PixelFormat::R8G8B8A8_UNORM,&colors);
        _defaultSampler = slag::TextureSamplerBuilder().setFilters(slag::TextureSampler::LINEAR).create();
        glm::vec3 pos1 = {1.f, 1.f, 0.0f};//bottom right
        glm::vec3 pos2 = {-1.f, 1.f, 0.0f};//bottom left
        glm::vec3 pos3 = {-1.f,-1.f, 0.0f};//top left
        glm::vec3 pos4 = {1.f,-1.f, 0.0f};//top right
        glm::vec3 normal = {0,0,0};
        glm::vec2  uv1 = {1,1};
        glm::vec2  uv2 = {0,1};
        glm::vec2  uv3 = {0,0};
        glm::vec2  uv4 = {1,0};
        std::vector<Vertex3D> verts ={{.position=pos1,.normal=normal,.uv = uv1},{.position=pos2,.normal=normal,.uv = uv2},{.position=pos3,.normal=normal,.uv = uv3},{.position=pos4,.normal=normal,.uv=uv4}};
        std::vector<uint16_t> indexes={0,1,2,2,3,0};
        _cube = new Mesh(verts,indexes);
        compShader = slag::ComputeShader::create("Graphics/DefaultShaders/test.comp.spv");
    }

    void Editor::setUpSwapchain(slag::SwapchainBuilder& builder)
    {
        Game::setUpSwapchain(builder);
        builder.addTextureResource("Depth",
        {
            .sizingMode=slag::TextureResourceDescription::FrameRelative,
            .width=1,
            .height=1,
            .mipLevels=1,
            .format= slag::Pixels::PixelFormat::D32_SFLOAT,
            .usage = slag::Texture::Usage::DEPTH,
            .features = slag::Texture::Features::DEPTH_ATTACHMENT
        });
        builder.addTextureResource("Color",{
                .sizingMode=slag::TextureResourceDescription::FrameRelative,
                .width=1,
                .height=1,
                .mipLevels=1,
                .format= slag::Pixels::PixelFormat::B8G8R8A8_UNORM,
                .usage = slag::Texture::Usage::COLOR,
                .features = slag::Texture::Features::COLOR_ATTACHMENT|slag::Texture::Features::SAMPLED_IMAGE|slag::Texture::Features::STORAGE
        });
        builder.setDesiredPixelFormat(slag::Pixels::PixelFormat::B8G8R8A8_SRGB);
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

        slag::CommandBuffer* commandBuffer = frame->getCommandBuffer();
        slag::UniformBuffer* uniformBuffer = frame->getUniformBuffer();
        slag::Texture* backBuffer = frame->getBackBuffer();
        slag::Texture* colorBuffer = frame->getTextureResource("Color");
        slag::Texture* depthBuffer = frame->getTextureResource("Depth");

        slag::ImageMemoryBarrier colorResetBarrier =
                {
                        .oldLayout = slag::Texture::Layout::UNDEFINED,
                        .newLayout = slag::Texture::Layout::GENERAL,
                        .requireCachesFinish = slag::PipelineAccess::PipeLineAccessFlags::ACCESS_MEMORY_WRITE_BIT,
                        .usingCaches = slag::PipelineAccess::PipeLineAccessFlags::NONE,
                        .texture = colorBuffer
                };
        commandBuffer->insertBarriers(nullptr,0,&colorResetBarrier,1, nullptr,0,slag::PipelineStage::TOP,slag::PipelineStage::PipelineStageFlags::STAGE_COMPUTE_SHADER);

        commandBuffer->bindShader(compShader);
        slag::UniformSetData compData(compShader->getUniformSet(0),frame->getUniformSetDataAllocator());
        compData.setImage(0,colorBuffer,slag::Texture::Layout::GENERAL);
        commandBuffer->bindUniformSetData(compShader,compData);
        commandBuffer->dispatch(colorBuffer->width()/16,backBuffer->height()/16,1);



        slag::ImageMemoryBarrier colorResetBarrier2 =
                {
                .oldLayout = slag::Texture::Layout::GENERAL,
                .newLayout = slag::Texture::Layout::RENDER_TARGET,
                .requireCachesFinish = slag::PipelineAccess::PipeLineAccessFlags::ACCESS_MEMORY_WRITE_BIT,
                .usingCaches = slag::PipelineAccess::PipeLineAccessFlags::ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                .texture = colorBuffer
                };
        commandBuffer->insertBarriers(nullptr,0,&colorResetBarrier2,1, nullptr,0,slag::PipelineStage::STAGE_COMPUTE_SHADER,slag::PipelineStage::PipelineStageFlags::ALL_GRAPHICS);

        slag::Rectangle view{{0,0},{ std::min(backBuffer->width(),depthBuffer->width()),std::min(backBuffer->height(),depthBuffer->height())}};
        if(backBuffer->width() > 0 && backBuffer->height() > 0)
        {
            commandBuffer->setViewport(view);
            commandBuffer->setScissors(view);
        }

        //not clearing color on load because the compute shader effectively clears it for us
        slag::Attachment renderSurface{.texture = colorBuffer, .clearOnLoad = false, .clear={0.5f, 0.5f, 0.5f, 1.0f}};
        slag::Attachment depthAttachment{.texture = depthBuffer,.clearOnLoad = true,.clear={1.0f,0}};
        commandBuffer->setTargetFramebuffer(view, &renderSurface, 1,depthAttachment);

        //interesting stuff here

        auto flatShader = ShaderLibrary::getMaterialShader("Flat");
        auto flatHandle =flatShader->handle();
        commandBuffer->bindShader(flatHandle);
        slag::UniformSetData globalData(flatHandle->getUniformSet(0),frame->getUniformSetDataAllocator());
        glm::mat4 ViewMatrix = glm::translate(glm::mat4(1), glm::vec3(0.5f, 0.0f ,0.0f));
        glm::mat4 projection=glm::perspective(90.0f,(float)(view.extent.width)/(float)(view.extent.height),0.0f,1.0f);//glm::ortho(-2.0f,2.0f,-2.0f,2.0f,.0f,1.0f);
        glm::mat4 mp = projection*ViewMatrix;
        auto globalWrite = uniformBuffer->write(&mp,sizeof(glm::mat4));
        globalData.setUniform(0,globalWrite);
        commandBuffer->bindUniformSetData(flatHandle,globalData);

        slag::UniformSetData instanceData(flatHandle->getUniformSet(1),frame->getUniformSetDataAllocator());
        glm::mat4 localMatrix(1);

        localMatrix = glm::translate(localMatrix,glm::vec3(0,0,-rotation/2));
        localMatrix = glm::rotate(localMatrix,rotation,glm::vec3(0,1,0));

        rotation+=.01;
        if(rotation > 10)
        {
            rotation = 0;
        }

        auto writeData = uniformBuffer->write(&localMatrix,sizeof(glm::mat4));
        instanceData.setUniform(0,writeData);
        instanceData.setTexture(1,_defaultTexture,_defaultSampler,slag::Texture::Layout::SHADER_RESOURCE);
        commandBuffer->bindUniformSetData(flatHandle,instanceData);
        commandBuffer->bindVertexBuffer(_cube->verticies());
        commandBuffer->bindIndexBuffer(_cube->indecies(),slag::GraphicsTypes::IndexType::UINT16);
        commandBuffer->drawIndexed(_cube->indeciesCount(),1,0,0,0);
        //end interesting stuff
        commandBuffer->endTargetFramebuffer();


        //blit color into backbuffer;
        slag::ImageMemoryBarrier barriers[2];
        barriers[0] =
                {
                        .oldLayout = slag::Texture::Layout::PRESENT,
                        .newLayout = slag::Texture::Layout::COPY_DESTINATION,
                        .requireCachesFinish = slag::PipelineAccess::PipeLineAccessFlags::ACCESS_MEMORY_READ_BIT,
                        .usingCaches = slag::PipelineAccess::PipeLineAccessFlags::ACCESS_MEMORY_WRITE_BIT,
                        .texture = backBuffer
                };
        barriers[1] =
                {
                        .oldLayout = slag::Texture::Layout::RENDER_TARGET,
                        .newLayout = slag::Texture::Layout::COPY_SOURCE,
                        .requireCachesFinish = slag::PipelineAccess::PipeLineAccessFlags::ACCESS_SHADER_WRITE_BIT,
                        .usingCaches = slag::PipelineAccess::PipeLineAccessFlags::ACCESS_MEMORY_READ_BIT,
                        .texture = colorBuffer
                };
        commandBuffer->insertBarriers(nullptr,0,barriers,2, nullptr,0,slag::PipelineStage::ALL_GRAPHICS,slag::PipelineStage::STAGE_TRANSFER);
        commandBuffer->blitImage(colorBuffer,view,slag::Texture::Layout::COPY_SOURCE,backBuffer,view,slag::Texture::Layout::COPY_DESTINATION,slag::TextureSampler::Filter::LINEAR);
        slag::ImageMemoryBarrier backBufferTransferBarrierEnd =
                {
                        .oldLayout = slag::Texture::Layout::COPY_DESTINATION,
                        .newLayout = slag::Texture::Layout::PRESENT,
                        .requireCachesFinish = slag::PipelineAccess::PipeLineAccessFlags::ACCESS_MEMORY_WRITE_BIT,
                        .usingCaches = slag::PipelineAccess::PipeLineAccessFlags::NONE,
                        .texture = backBuffer
                };
        commandBuffer->insertBarriers(nullptr,0,&backBufferTransferBarrierEnd,1, nullptr,0,slag::PipelineStage::STAGE_TRANSFER,slag::PipelineStage::BOTTOM);

        frame->end();
    }

    void Editor::cleanup()
    {
        delete _defaultTexture;
        delete _defaultSampler;
        delete _cube;
        delete compShader;
    }


    Editor* Editor::createNewEditor(void *nativeHandle)
    {
        int i=0;
        std::lock_guard<std::mutex> guard(EDITORS_MUTEX);
        Editor* e = new Editor(nativeHandle);
        OPEN_EDITORS.insert(e);
        return e;
    }

    void Editor::destroyEditor(Editor* editor_ptr)
    {
        std::lock_guard<std::mutex> guard(EDITORS_MUTEX);
        OPEN_EDITORS.erase(editor_ptr);
        delete editor_ptr;
    }

    void Editor::startGraphicsQueue()
    {
        RENDER_THREAD = new std::thread([]
                                        {

                                            Uint64 now = SDL_GetPerformanceCounter();
                                            Uint64 last = 0;
                                            float deltaTime = 0;
                                            while(PROCESS_EDITORS)
                                            {

                                                {
                                                    std::lock_guard<std::mutex> guard(EDITORS_MUTEX);
                                                    for (auto editor: OPEN_EDITORS)
                                                    {
                                                        editor->runFrame(deltaTime);
                                                    }
                                                }
                                                //I don't know why, but if we don't sleep, the locking on the mutexes takes FOREVER
                                                std::this_thread::sleep_for(std::chrono::microseconds(1));
                                                last = now;
                                                now = SDL_GetPerformanceCounter();
                                                deltaTime = ((now - last)*1000 / (float)SDL_GetPerformanceFrequency());
                                            }

                                        });
    }

    void Editor::endGraphicsQueue()
    {
        PROCESS_EDITORS = false;
        RENDER_THREAD->join();
        for(auto& editor_ptr: OPEN_EDITORS)
        {
            delete editor_ptr;
        }
        OPEN_EDITORS.clear();

        delete RENDER_THREAD;
        RENDER_THREAD = nullptr;
    }

    Editor::~Editor()
    {
        teardownResources();
    }

} // crucible
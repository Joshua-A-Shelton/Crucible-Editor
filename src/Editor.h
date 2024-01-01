#ifndef CRUCIBLEEDITOR_EDITOR_H
#define CRUCIBLEEDITOR_EDITOR_H
#include <crucible/Game.h>
#include "imgui.h"
#include <slag/SlagLib.h>

namespace crucible
{

    class Editor: public Game
    {
    public:
        void initialize(const char* gameName,const char* iconPath)override;
        void setUpSwapchain(slag::SwapchainBuilder& builder)override;
        void processEvents()override;
        void update(float deltaTime)override;
        void render(slag::Frame* frame)override;
        void cleanup()override;
    private:
        ImFont* Title;
        ImFont* Body;


        void (*drawInterface)() = nullptr;
        void (*setSceneTexture)(slag::Texture*) = nullptr;

        static void resizeMainViewPortTexture(float width, float height);
    };

} // crucible

#endif //CRUCIBLEEDITOR_EDITOR_H

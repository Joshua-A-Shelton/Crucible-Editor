#ifndef CRUCIBLEEDITOR_EDITOR_H
#define CRUCIBLEEDITOR_EDITOR_H
#include <crucible/Game.h>
#include <slag/SlagLib.h>
#include <crucible/Graphics/Mesh.h>

namespace crucible
{

    class Editor: public Game
    {
    public:
        Editor(void* nativeHandle= nullptr);
        ~Editor();
        void initialize(const char* gameName,const char* iconPath)override;
        void setUpSwapchain(slag::SwapchainBuilder& builder)override;
        void processEvents()override;
        void update(float deltaTime)override;
        void render(slag::Frame* frame)override;
        void cleanup()override;
        static Editor* createNewEditor(void* nativeHandle);
        static void destroyEditor(Editor* editor_ptr);
        static void startGraphicsQueue();
        static void endGraphicsQueue();
    private:
        slag::Texture* _defaultTexture = nullptr;
        slag::TextureSampler* _defaultSampler = nullptr;
        crucible::Mesh* _cube = nullptr;
    };

} // crucible

#endif //CRUCIBLEEDITOR_EDITOR_H

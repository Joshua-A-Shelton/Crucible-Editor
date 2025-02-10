#ifndef CRUCIBLEEDITOR_EDITOR_H
#define CRUCIBLEEDITOR_EDITOR_H
#include <crucible/Crucible.h>
namespace crucible
{

    class Editor: public crucible::Game
    {
    public:
        Editor(slag::Sampler* UiSampler);
        ~Editor();
        Editor(const Editor&)=delete;
        Editor& operator=(const Editor&)=delete;
        Editor(Editor&& from)=delete;
        Editor& operator=(Editor&& from);
        void handleEvent(SDL_Event& event)override;
        void update(double deltaTime)override;
        void draw(slag::CommandBuffer* commandBuffer, slag::Texture* drawBuffer, slag::DescriptorPool* descriptorPool)override;
    private:
        void move(Editor& from);
    };

} // crucible

#endif //CRUCIBLEEDITOR_EDITOR_H

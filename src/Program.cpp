#define SDL_MAIN_HANDLED
#include <crucible/Engine.h>

#include "Editor.h"


int main(int argc, char** args)
{
    crucible::Engine::initialize();
    crucible::Editor editor;
    editor.run("Crucible Editor","Crucible.png");
    crucible::Engine::cleanup();
}
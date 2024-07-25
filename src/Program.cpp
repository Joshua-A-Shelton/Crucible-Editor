#define SDL_MAIN_HANDLED
#include <crucible/Engine.h>
#include "crucible/Scripting/ScriptingEngine.h"
#include <crucible/Graphics/Shaders/ShaderLibrary.h>
#include "Interop/EditorInterop.h"
#include "Editor.h"

int main(int argc, char** args)
{
    crucible::Engine::initialize();

    crucible::ScriptingEngine::loadManagedDll("CrucibleEditor","Crucible-Editor.dll");

    crucible::EditorInterop::registerInteropFunctions();
    auto avaloniaMainClass = crucible::ScriptingEngine::getManagedType("CrucibleEditor.Main, Crucible-Editor");
    auto avaloniaMain = avaloniaMainClass.getFunction<void(*)()>("AvaloniaMain");
    crucible::ShaderLibrary::loadMaterialShader("Graphics/DefaultShaders/flat.vert.spv","Graphics/DefaultShaders/flat.frag.spv","Flat");
    crucible::Editor::startGraphicsQueue();
    avaloniaMain();
    crucible::Editor::endGraphicsQueue();
    crucible::ShaderLibrary::unloadShaders();
    crucible::ScriptingEngine::unloadManagedDllContext("CrucibleEditor");
    crucible::Engine::cleanup();
}
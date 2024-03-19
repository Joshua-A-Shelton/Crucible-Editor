#define SDL_MAIN_HANDLED
#include <crucible/Engine.h>
#include "crucible/Scripting/ScriptingEngine.h"
#include "Interop/EditorInterop.h"

int main(int argc, char** args)
{
    crucible::Engine::initialize();

    crucible::ScriptingEngine::loadManagedDll("CrucibleEditor","Crucible-Editor.dll");

    crucible::EditorInterop::registerInteropFunctions();
    auto avaloniaMainClass = crucible::ScriptingEngine::getManagedType("CrucibleEditor.Main, Crucible-Editor");
    auto avaloniaMain = avaloniaMainClass.getFunction<void(*)()>("AvaloniaMain");
    avaloniaMain();
    crucible::ScriptingEngine::unloadManagedDllContext("CrucibleEditor");
    crucible::Engine::cleanup();
}
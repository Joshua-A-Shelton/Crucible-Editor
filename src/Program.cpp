#define SDL_MAIN_HANDLED
#include <crucible/Engine.h>
#include "crucible/Scripting/ScriptingEngine.h"
#include "Interop/EditorInterop.h"

int main(int argc, char** args)
{
    crucible::Engine::initialize();
    //crucible::Editor editor;
    //editor.run("Crucible Editor","Crucible.png");
    crucible::ScriptingEngine::loadManagedDll("CrucibleEditor","Crucible-Editor.dll");
    //for some reason, these need to be loaded manually
    /*crucible::ScriptingEngine::loadManagedDll("CrucibleEditor","NP.Ava.UniDock.dll");
    crucible::ScriptingEngine::loadManagedDll("CrucibleEditor","NP.Ava.UniDockService.dll");
    crucible::ScriptingEngine::loadManagedDll("CrucibleEditor","NP.Ava.Visuals.dll");
    crucible::ScriptingEngine::loadManagedDll("CrucibleEditor","NP.Ava.UniDock.dll");
    crucible::ScriptingEngine::loadManagedDll("CrucibleEditor","NP.Concepts.Behaviors.dll");
    crucible::ScriptingEngine::loadManagedDll("CrucibleEditor","NP.Utilities.dll");
    crucible::ScriptingEngine::loadManagedDll("CrucibleEditor","System.Reactive.dll");*/

    crucible::EditorInterop::registerInteropFunctions();
    auto avaloniaMainClass = crucible::ScriptingEngine::getManagedType("CrucibleEditor.Main, Crucible-Editor");
    auto avaloniaMain = avaloniaMainClass.getFunction<void(*)()>("AvaloniaMain");
    avaloniaMain();
    crucible::ScriptingEngine::unloadManagedDllContext("CrucibleEditor");
    crucible::Engine::cleanup();
}
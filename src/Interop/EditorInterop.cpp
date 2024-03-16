#include "EditorInterop.h"
#include <crucible/Scripting/ScriptingEngine.h>
#include "../Editor.h"
namespace crucible
{
    void EditorInterop::registerInteropFunctions()
    {
        //crucible::ScriptingEngine::registerUnmanagedFunction("CrucibleEditor.Controls.SceneView, Crucible-Editor", "_createSceneView", reinterpret_cast<void **>(Editor::createNewEditor));
    }
} // crucible
#include "ImGuiInterop.h"
#include <crucible/Scripting/ScriptingEngine.h>
#include <imgui.h>
namespace crucible
{
    bool imGuiTreeNode_void_string(void* id, const char* fmt)
    {
        return ImGui::TreeNode(id,fmt);
    }
    bool imGuiTreeNode_string_string(const char* id ,const char* fmt)
    {
        return ImGui::TreeNode(id,fmt);
    }
    void ImGuiInterop::registerInteropFunctions()
    {
        auto from = "CrucibleEditor.GUI.ImGUI, Crucible-Editor";
        ScriptingEngine::registerUnmanagedFunction(from, "_begin_ptr", reinterpret_cast<void **>(ImGui::Begin));
        ScriptingEngine::registerUnmanagedFunction(from, "_end_ptr", reinterpret_cast<void **>(ImGui::End));
        ScriptingEngine::registerUnmanagedFunction(from, "_label_ptr", reinterpret_cast<void **>(ImGui::LabelText));
        ScriptingEngine::registerUnmanagedFunction(from,"_treeNode_string_ptr",reinterpret_cast<void **>((bool(*)(const char*))ImGui::TreeNode));
        ScriptingEngine::registerUnmanagedFunction(from, "_treeNode_void_string_ptr", reinterpret_cast<void **>(imGuiTreeNode_void_string));
        ScriptingEngine::registerUnmanagedFunction(from, "_treeNode_string_string", reinterpret_cast<void **>(imGuiTreeNode_string_string));
        ScriptingEngine::registerUnmanagedFunction(from, "_treeNodePop_ptr", reinterpret_cast<void **>(ImGui::TreePop));
        ScriptingEngine::registerUnmanagedFunction(from, "_openPopup_ptr", reinterpret_cast<void **>((void (*)(const char *, ImGuiPopupFlags)) ImGui::OpenPopup));
        ScriptingEngine::registerUnmanagedFunction(from, "_beginPopup_ptr", reinterpret_cast<void **>(ImGui::BeginPopup));
        ScriptingEngine::registerUnmanagedFunction(from, "_endPopup_ptr", reinterpret_cast<void **>(ImGui::EndPopup));
        ScriptingEngine::registerUnmanagedFunction(from, "_selectable_ptr", reinterpret_cast<void **>((bool (*)(const char *, bool*, ImGuiSelectableFlags, const ImVec2 &)) ImGui::Selectable));
    }
} // crucible
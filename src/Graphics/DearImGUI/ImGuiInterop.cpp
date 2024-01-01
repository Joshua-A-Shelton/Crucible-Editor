#include "ImGuiInterop.h"
#include <crucible/Scripting/ScriptingEngine.h>
#include <iostream>


namespace crucible
{
    ImFont* IMGUI_TITLE_FONT = nullptr;
    ImFont* IMGUI_BODY_FONT = nullptr;

    void pushTitleFont()
    {
        ImGui::PushFont(IMGUI_TITLE_FONT);
    }
    void pushBodyFont()
    {
        ImGui::PushFont(IMGUI_BODY_FONT);
    }

    bool imGuiTreeNode_void_string(void* id, const char* fmt)
    {
        return ImGui::TreeNode(id,fmt);
    }
    bool imGuiTreeNode_string_string(const char* id ,const char* fmt)
    {
        return ImGui::TreeNode(id,fmt);
    }

    void GetContentRegionAvail(ImVec2& ref)
    {
        ref = ImGui::GetContentRegionAvail();
    }


    void ImGuiInterop::registerInteropFunctions(ImFont* title, ImFont* body)
    {
        auto from = "CrucibleEditor.GUI.ImGUI, Crucible-Editor";
        IMGUI_TITLE_FONT = title;
        IMGUI_BODY_FONT = body;
        ScriptingEngine::registerUnmanagedFunction(from, "_begin_ptr", reinterpret_cast<void **>(ImGui::Begin));
        ScriptingEngine::registerUnmanagedFunction(from, "_end_ptr", reinterpret_cast<void **>(ImGui::End));
        ScriptingEngine::registerUnmanagedFunction(from, "_pushTitleFont_ptr", reinterpret_cast<void **>(pushTitleFont));
        ScriptingEngine::registerUnmanagedFunction(from, "_pushBodyFont_ptr", reinterpret_cast<void **>(pushBodyFont));
        ScriptingEngine::registerUnmanagedFunction(from, "_popFont_ptr", reinterpret_cast<void **>(ImGui::PopFont));
        ScriptingEngine::registerUnmanagedFunction(from, "_collapsingHeader_ptr", reinterpret_cast<void **>((bool (*)(const char *, ImGuiTreeNodeFlags)) ImGui::CollapsingHeader));
        ScriptingEngine::registerUnmanagedFunction(from, "_label_ptr", reinterpret_cast<void **>(ImGui::LabelText));
        ScriptingEngine::registerUnmanagedFunction(from,"_treeNode_string_ptr",reinterpret_cast<void **>((bool(*)(const char*))ImGui::TreeNode));
        ScriptingEngine::registerUnmanagedFunction(from, "_treeNode_void_string_ptr", reinterpret_cast<void **>(imGuiTreeNode_void_string));
        ScriptingEngine::registerUnmanagedFunction(from, "_treeNode_string_string", reinterpret_cast<void **>(imGuiTreeNode_string_string));
        ScriptingEngine::registerUnmanagedFunction(from, "_treeNodePop_ptr", reinterpret_cast<void **>(ImGui::TreePop));
        ScriptingEngine::registerUnmanagedFunction(from, "_openPopup_ptr", reinterpret_cast<void **>((void (*)(const char *, ImGuiPopupFlags)) ImGui::OpenPopup));
        ScriptingEngine::registerUnmanagedFunction(from, "_beginPopup_ptr", reinterpret_cast<void **>(ImGui::BeginPopup));
        ScriptingEngine::registerUnmanagedFunction(from, "_endPopup_ptr", reinterpret_cast<void **>(ImGui::EndPopup));
        ScriptingEngine::registerUnmanagedFunction(from, "_selectable_ptr", reinterpret_cast<void **>((bool (*)(const char *, bool*, ImGuiSelectableFlags, const ImVec2 &)) ImGui::Selectable));
        ScriptingEngine::registerUnmanagedFunction(from, "_image_ptr", reinterpret_cast<void **>(ImGui::Image));
        ScriptingEngine::registerUnmanagedFunction(from, "_getContentRegionAvail_ptr", reinterpret_cast<void **>(GetContentRegionAvail));
    }
} // crucible
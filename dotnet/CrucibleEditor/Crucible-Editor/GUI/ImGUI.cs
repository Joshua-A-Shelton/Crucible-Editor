using Crucible;

namespace CrucibleEditor.GUI;

#pragma warning disable 0649
internal static unsafe class ImGUI
{
    public enum Flags
    {
        
    }
    
    private static delegate* unmanaged<string,bool *,int,bool> _begin_ptr;

    public static void Begin(string title, int flags = 0)
    {
        _begin_ptr(title, null, 0);
    }
    public static bool BeginClosable(string title, int flags = 0)
    {
        bool isOpen=false;
        _begin_ptr(title, &isOpen, flags);
        return isOpen;
    }
    
    
    private static delegate* unmanaged<void> _end_ptr;
    public static void End()
    {
        _end_ptr();
    }

    private static delegate* unmanaged<string, string, void> _label_ptr;

    public static void Label(string text, string label)
    {
        _label_ptr(text, label);
    }

    private static delegate* unmanaged<string, bool> _treeNode_string_ptr;
    public static bool TreeNode(string label)
    {
        return _treeNode_string_ptr(label);
    }

    private static delegate* unmanaged<string, string, bool> _treeNode_string_string;

    public static bool TreeNode(string id, string label)
    {
        return _treeNode_string_string(id, label);
    }

    private static delegate* unmanaged<object, string, bool> _treeNode_void_string_ptr;

    public static bool TreeNode(object obj, string label)
    {
        return _treeNode_void_string_ptr(obj, label);
    }
    
    

    private static delegate* unmanaged<void> _treeNodePop_ptr;
    public static void TreePop()
    {
        _treeNodePop_ptr();
    }

    private static delegate* unmanaged<string, int, void> _openPopup_ptr;

    public static void OpenPopup(string id, int flags = 0)
    {
        _openPopup_ptr(id,flags);
    }

    private static delegate* unmanaged<string, int, bool> _beginPopup_ptr;
    public static bool BeginPopup(string id, int flags = 0)
    {
        return _beginPopup_ptr(id, flags);
    }

    private static delegate* unmanaged<void> _endPopup_ptr;

    public static void EndPopup()
    {
        _endPopup_ptr();
    }

    private static delegate* unmanaged<string, ref bool, int, ref Vector2,bool> _selectable_ptr;

    public static bool Selectable(string label, ref bool isSelected, int flags, ref Vector2 size)
    {
        return _selectable_ptr(label, ref isSelected, flags, ref size);
    }
}
#pragma warning restore 0649
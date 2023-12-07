using System.Reflection;
using Crucible;
using CrucibleEditor.GUI;
using CrucibleEditor.GUI.Controls;

namespace CrucibleEditor.Util;

internal static class GameObjectExtensions
{
    public static void DrawComponents(this GameObject gameObject)
    {
        var types = gameObject.ComponentTypes();
        foreach (var compenentType in types)
        {
            typeof(GameObjectExtensions).GetMethod("DrawComponent", BindingFlags.Static | BindingFlags.NonPublic)?
                .MakeGenericMethod(compenentType).Invoke(null, new[] {gameObject});
        }
    }

    private static void DrawComponent<T>(GameObject gameObject)
    {
        ref T mycomponent = ref gameObject.GetComponent<T>();
        InspectorRenderer.DrawComponent(ref mycomponent);
    }
    
    public static void RenderTreeNode(this GameObject gameObject)
    {
        if (ImGUI.TreeNode(gameObject.Uuid.ToString(),gameObject.Name))
        {
            bool isSelected = false;
            Vector2 v = new Vector2();
            ImGUI.Selectable(gameObject.Uuid.ToString(),ref isSelected,0,ref v);
            if (isSelected)
            {
                ProgramInterface.SelectedGameObject = gameObject;
            }
            /*ImGUI.OpenPopup(gameObject.Uuid.ToString());
            if (ImGUI.BeginPopup(gameObject.Uuid.ToString()))
            {
                ImGUI.Label("I'm a popup","for this guy");
                ImGUI.EndPopup();
            }*/
            foreach (var child in gameObject.Children)
            {
                child.RenderTreeNode();
            }
            ImGUI.TreePop();
        }
    }
}
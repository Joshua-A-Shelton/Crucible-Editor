using Crucible;
using CrucibleEditor.Util;

namespace CrucibleEditor.GUI.Widgets;

public class SceneTree: Widget
{
    public SceneTree()
    {
        Title = "Scene Tree";
        CanClose = false;
        var go = GameWorld.Scene.GameObjects.ElementAt(0);
        go.Name = "My First Object";
        go.AddComponent(new Transform3D());
        GameObject child = new GameObject();
        child.Name = "child";
        go.AddChild(child);
        GameWorld.Scene.GameObjects.Add(new GameObject());
        GameWorld.Scene.GameObjects.ElementAt(1).Name = "My First Object";
    }
    protected override void Render()
    {
        foreach (var gameObject in GameWorld.Scene.GameObjects)
        {
            gameObject.RenderTreeNode();
        }
    }
}
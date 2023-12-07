using Crucible;
using CrucibleEditor.GUI.Widgets;

namespace CrucibleEditor.GUI;

public static class ProgramInterface
{
    public static MainViewport MainViewport = new MainViewport();
    public static Inspector Inspector = new Inspector();
    public static SceneTree SceneTree = new SceneTree();
    public static Resources Resources = new Resources();

    public static GameObject? SelectedGameObject = null;
    
    
    public static void DrawInterface()
    {
        try
        {
            MainViewport.Draw();
            Inspector.Draw();   
            SceneTree.Draw();
            Resources.Draw();
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
            throw;
        }

    }
}
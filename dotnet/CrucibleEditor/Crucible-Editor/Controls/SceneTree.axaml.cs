using System.ComponentModel;
using System.Runtime.CompilerServices;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;
using Crucible;

namespace CrucibleEditor.Controls;

public partial class SceneTree : UserControl
{
    public Scene CurrentScene
    {
        get { return GameWorld.Scene; }
    }
    
    public List<GameObject> GameObjects
    {
        get { return CurrentScene.GameObjects; }
    }
    public SceneTree()
    {
        InitializeComponent();
    }
}
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;
using Crucible;
using Crucible.Nodes;

namespace CrucibleEditor.Controls;

public partial class SceneTree : UserControl
{
    public Scene CurrentScene
    {
        get { return GameWorld.Scene; }
    }
    
    public List<Node> GameObjects
    {
        get { return CurrentScene.Nodes; }
    }
    public SceneTree()
    {
        InitializeComponent();
    }
}
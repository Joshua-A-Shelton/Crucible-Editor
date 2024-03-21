using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;
using Crucible;

namespace CrucibleEditor.Controls.Components;

public partial class Transform3dViewer : ComponentViewer<Transform3D>
{
    
    Vector3 v = new Vector3(15, 1, 30);
    public Transform3dViewer()
    {
        InitializeComponent();
    }

    public override void UpdateEditors()
    {
        v.y *= 1.001f;
        Position.SyncProperty(ref v);
    }
}
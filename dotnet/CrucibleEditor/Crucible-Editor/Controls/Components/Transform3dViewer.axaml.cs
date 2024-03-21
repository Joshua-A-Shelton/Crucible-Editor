using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;
using Crucible;

namespace CrucibleEditor.Controls.Components;

public partial class Transform3dViewer : ComponentViewer<Transform3D>
{
    
    public Transform3dViewer()
    {
        InitializeComponent();
    }
    
    protected override void UpdateEditors(ref Transform3D component)
    {
        var v3 = component.Position;
        Position.SyncProperty(ref v3);
        component.Position = v3;
    }
}
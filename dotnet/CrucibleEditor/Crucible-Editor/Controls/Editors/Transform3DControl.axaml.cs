using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;
using Crucible;

namespace CrucibleEditor.Controls.Editors;

public partial class Transform3DControl : ComponentEditor<Transform3D>
{
    public Transform3DControl(): base()
    {
        InitializeComponent();
    }
}
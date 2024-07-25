using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;
using Crucible;

namespace CrucibleEditor.Editors.PropertyControls.Defaults;

public partial class Transform3DControl : PropertyControl<Transform3D>
{
    public Transform3DControl()
    {
        InitializeComponent();
    }
}
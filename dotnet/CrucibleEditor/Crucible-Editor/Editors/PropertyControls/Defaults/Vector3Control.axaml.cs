using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;

namespace CrucibleEditor.Editors.PropertyControls.Defaults;

public partial class Vector3Control : PropertyControl<Vector3D>
{
    public Vector3Control()
    {
        InitializeComponent();
    }
}
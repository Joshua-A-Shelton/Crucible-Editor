using Avalonia;
using Avalonia.Controls;
using Crucible.Nodes;

namespace CrucibleEditor.Editors;

public abstract class AbstractEditor:  UserControl
{

    public static readonly StyledProperty<Node> EditingProperty =
        AvaloniaProperty.Register<AbstractEditor, Node>(nameof(Editing));
    public Node Editing
    {
        get { return GetValue(EditingProperty); }
        set { SetValue(EditingProperty, value); }
    }
}
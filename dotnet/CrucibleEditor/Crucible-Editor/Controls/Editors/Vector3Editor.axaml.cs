using System.ComponentModel;
using System.Runtime.CompilerServices;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Data;
using Avalonia.Markup.Xaml;
using Crucible;

namespace CrucibleEditor.Controls.Editors;

public partial class Vector3Editor : Editor<Crucible.Vector3>
{
    public static readonly DirectProperty<Vector3Editor, float> XProperty = AvaloniaProperty.RegisterDirect<Vector3Editor, float>(nameof(X),
        vector3Editor => vector3Editor.X,
        (vector3Editor, val) => vector3Editor.X = val);
    
    public static readonly DirectProperty<Vector3Editor, float> YProperty = AvaloniaProperty.RegisterDirect<Vector3Editor, float>(nameof(Y),
        vector3Editor => vector3Editor.Y,
        (vector3Editor, val) => vector3Editor.Y = val);
    
    public static readonly DirectProperty<Vector3Editor, float> ZProperty = AvaloniaProperty.RegisterDirect<Vector3Editor, float>(nameof(Z),
        vector3Editor => vector3Editor.Z,
        (vector3Editor, val) => vector3Editor.Z = val);
    public float X
    {
        get { return Editing.x; }
        set
        {
            SetAndRaise(XProperty, ref _editing.x, value);
            Editing = _editing;
        }
    }
    
    public float Y
    {
        get { return Editing.y; }
        set
        {
            SetAndRaise(YProperty, ref _editing.y, value);
            Editing = _editing;
        }
    }

    public float Z
    {
        get { return Editing.z; }
        set
        {
            SetAndRaise(ZProperty, ref _editing.z, value);
            Editing = _editing;
        }
    }
    public Vector3Editor()
    {
        InitializeComponent();
    }
}
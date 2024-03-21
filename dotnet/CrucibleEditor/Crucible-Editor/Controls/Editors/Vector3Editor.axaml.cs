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
        get { return EditorValue.x; }
        set { SetAndRaise(XProperty, ref _editorValue.x, value); }
    }

    public float Y
    {
        get { return EditorValue.y; }
        set { SetAndRaise(XProperty, ref _editorValue.y, value);}
    }

    public float Z
    {
        get { return EditorValue.z; }
        set { SetAndRaise(XProperty, ref _editorValue.z, value); }
    }
    public Vector3Editor()
    {
        PropertyChanged += parentChanged;
        InitializeComponent();
    }

    public void parentChanged(object sender, AvaloniaPropertyChangedEventArgs e)
    {
        if (e.Property == EditorValueProperty)
        {
            var v3 = e.GetNewValue<Vector3>();
            X = v3.x;
            Y = v3.y;
            Z = v3.z;
        };
    }
    
}
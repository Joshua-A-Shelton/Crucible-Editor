using System.ComponentModel;
using System.Runtime.CompilerServices;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Data;

namespace CrucibleEditor.Controls.Editors;

public abstract class Editor<T>: UserControl
{
    public static readonly DirectProperty<Editor<T>, T> EditorValueProperty =
        AvaloniaProperty.RegisterDirect<Editor<T>, T>(nameof(EditorValue),
            o=>o.EditorValue,
            (o,v)=> o.EditorValue = v);

    private bool _editorUpdated = false;
    protected T _editorValue;
    public T EditorValue
    {
        get { return _editorValue; }
        set { SetAndRaise(EditorValueProperty, ref _editorValue, value);
            _editorUpdated = true;
        }
    }
    public void SyncProperty(ref T runtime)
    {
        if (_editorUpdated)
        {
            runtime = _editorValue;
        }
        else
        {
            EditorValue = runtime;
        }
        _editorUpdated = false;
    }
    
}
using System.ComponentModel;
using System.Runtime.CompilerServices;
using Avalonia;
using Avalonia.Controls;
using Avalonia.Data;

namespace CrucibleEditor.Controls.Editors;

public abstract class Editor<T>: UserControl
{

    public static readonly DirectProperty<Editor<T>, T> EditingProperty =
        AvaloniaProperty.RegisterDirect<Editor<T>, T>(nameof(Editing),o=>o.Editing, (o, v) => { o.Editing = v;});

    protected T _editing;
    private bool _fromEditor = false;
    public T Editing
    {
        get { return _editing;}
        set 
        {
            SetAndRaise(EditingProperty, ref _editing, value);
            _fromEditor = true;
        }
    }
    
    public Editor()
    {

    }

    public virtual void Sync(ref T with)
    {
        if (_fromEditor)
        {
            with = Editing;
        }
        else
        {
            Editing = with;
        }
        _fromEditor = false;
    }
    

}
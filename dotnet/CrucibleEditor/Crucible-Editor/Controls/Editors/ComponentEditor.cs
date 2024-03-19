using System.ComponentModel;
using Avalonia.Controls;
using Avalonia.Media;
using Crucible;

namespace CrucibleEditor.Controls.Editors;

public abstract class ComponentEditor<T> : UserControl
{
    private T _component;
    public T Component
    {
        get { return _component;}
        set { _component = value; OnPropertyChanged(nameof(Component)); }
    }

    internal void setComponentInit(object component)
    {
        if (component is T compObj)
        {
            Component = compObj;
            ComponentSet();
        }
        else
        {
            throw new ArgumentException("param \"" + nameof(component) + "\" must match type \"" + this.GetType().ToString() + "\"");
        }
    }
    
    public virtual void ComponentSet(){}
    
    public event PropertyChangedEventHandler PropertyChangedHandler;
    protected virtual void OnPropertyChanged(string propertyName)
    {
        PropertyChangedHandler?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
    
    public override void Render(DrawingContext context)
    {
        //There may be changes from anywhere, signal the change every time we draw just to be safe
        OnPropertyChanged(nameof(Component));
        base.Render(context);
    }
}
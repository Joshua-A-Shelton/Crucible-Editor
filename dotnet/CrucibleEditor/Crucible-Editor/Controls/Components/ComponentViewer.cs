using Avalonia.Controls;
using Avalonia.Media;
using Avalonia.Threading;
using Crucible;

namespace CrucibleEditor.Controls.Components;

public abstract class ComponentViewer<T>: UserControl
{
    protected abstract void UpdateEditors(ref T component);
    public WeakReference<GameObject> ReferenceObject = new WeakReference<GameObject>(null);

    public override void Render(DrawingContext context)
    {
        Dispatcher.UIThread.InvokeAsync(updateAndRedraw, DispatcherPriority.Background);
        base.Render(context);
    }

    private void updateAndRedraw()
    {
        GameObject go;
        if (ReferenceObject.TryGetTarget(out go) && go !=null)
        {
            UpdateEditors(ref go.GetComponent<T>());
            InvalidateVisual();
        }
        
    }
    
    
}
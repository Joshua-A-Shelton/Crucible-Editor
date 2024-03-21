using Avalonia.Controls;
using Avalonia.Media;
using Avalonia.Threading;

namespace CrucibleEditor.Controls.Components;

public abstract class ComponentViewer<T>: UserControl
{
    public abstract void UpdateEditors();

    public override void Render(DrawingContext context)
    {
        Dispatcher.UIThread.InvokeAsync(updateAndRedraw, DispatcherPriority.Background);
        base.Render(context);
    }

    private void updateAndRedraw()
    {
        UpdateEditors();
        InvalidateVisual();
    }
    
    
}
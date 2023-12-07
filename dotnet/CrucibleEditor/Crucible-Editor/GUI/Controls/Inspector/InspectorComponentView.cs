namespace CrucibleEditor.GUI.Controls.Inspector;

public abstract class InspectorComponentView<T>
{
    public abstract void Draw(ref T component);
}
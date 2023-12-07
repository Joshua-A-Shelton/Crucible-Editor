using Crucible;

namespace CrucibleEditor.GUI.Controls.Inspector;

public class TransformView: InspectorComponentView<Transform3D>
{
    public override void Draw(ref Transform3D component)
    {
        Vector3 position = component.Position;
        InspectorRenderer.DrawComponent(ref position);
        Console.WriteLine(component.Position);
    }
}
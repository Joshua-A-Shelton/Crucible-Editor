using Crucible;

namespace CrucibleEditor.GUI.Controls.Inspector;

public class Vector3dView: InspectorComponentView<Vector3>
{
    public override void Draw(ref Vector3 component)
    {
        ImGUI.Label(component.x.ToString(),"x");
        ImGUI.Label(component.y.ToString(),"y");
        ImGUI.Label(component.z.ToString(),"z");
    }
}
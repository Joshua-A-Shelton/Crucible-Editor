using Arch.Core.Extensions;
using Crucible;
using CrucibleEditor.GUI.Controls;
using CrucibleEditor.GUI.Controls.Inspector;
using CrucibleEditor.Util;

namespace CrucibleEditor.GUI.Widgets;

public class Inspector: Widget
{
    public Inspector()
    {
        Title = "Inspector";
        CanClose = false;
    }

    static Inspector()
    {
        InspectorRenderer.RegisterRenderer(typeof(Transform3D),new TransformView());
        InspectorRenderer.RegisterRenderer(typeof(Vector3), new Vector3dView());
    }
    protected override void Render()
    {
        GameObject? selectedGameObject = ProgramInterface.SelectedGameObject;
        if (selectedGameObject != null)
        {
            selectedGameObject.DrawComponents();
        }
    }
}
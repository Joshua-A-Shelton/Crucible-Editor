using System.Reflection;
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
        InspectorRenderer.RegisterRenderer(new TransformView());
        InspectorRenderer.RegisterRenderer(new Vector3dView());
    }
    protected override void Render()
    {
        GameObject? selectedGameObject = ProgramInterface.SelectedGameObject;
        if (selectedGameObject != null)
        {
            selectedGameObject.DrawComponents();
        }
    }

    public static string ExposedName(Type type, string fieldName)
    {
        var member = type.GetMember(fieldName, BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance).Where(mi=>Attribute.IsDefined(mi,typeof(ExposeAttribute)));
        if (member == null)
        {
            throw new ArgumentException("Field \"" + fieldName + "\" is not exposed for type \"" + type + "\"");
        }

        var mi = member.ElementAt(0);
        ExposeAttribute? exposeAttribute = mi.GetCustomAttribute(typeof(ExposeAttribute)) as ExposeAttribute;
        if (exposeAttribute != null && exposeAttribute.Name != null)
        {
            return exposeAttribute.Name;
        }

        return fieldName;
    }
}
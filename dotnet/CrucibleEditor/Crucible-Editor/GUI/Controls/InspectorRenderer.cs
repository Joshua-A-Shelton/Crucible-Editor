using System.Reflection;
using CrucibleEditor.GUI.Controls.Inspector;
using Crucible;
using CrucibleEditor.Util;

namespace CrucibleEditor.GUI.Controls;

public static class InspectorRenderer
{
    private static Dictionary<Type, object> _renderers = new Dictionary<Type, object>();

    internal static void RegisterRenderer(Type forComponent,object renderer)
    {
        /*if (!rendererType.IsSubclassOf(typeof(InspectorComponentView<>)))
        {
            throw new ArgumentException("rendererType must inherit InspectorComponentView");
        }*/

        _renderers[forComponent] = renderer;

    }
    public static void DrawComponent<T>(ref T component)
    {
        if (component != null)
        {
            string title = component.GetType().Name;
            var componentAttribute = typeof(T).GetCustomAttribute(typeof(ComponentAttribute)) as ComponentAttribute;
            if (componentAttribute != null && componentAttribute.ExposedName != null)
            {
                title = componentAttribute.ExposedName;
            }
            ImGUI.Label("##Component",title);

            object? componentRenderer;
            if (_renderers.TryGetValue(typeof(T), out componentRenderer))
            {
                InspectorComponentView<T> compRenderer = (InspectorComponentView<T>) componentRenderer;
                compRenderer.Draw(ref component);
            }
        }
    }

    public static void DrawMember<T>(ref T component)
    {
        object? componentView = null;
        if (_renderers.TryGetValue(typeof(T), out componentView))
        {
            InspectorComponentView<T> compRenderer = (InspectorComponentView<T>) componentView;
            compRenderer.Draw(ref component);
        }
    }
}
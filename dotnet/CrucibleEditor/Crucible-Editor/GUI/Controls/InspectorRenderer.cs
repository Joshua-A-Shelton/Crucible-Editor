using System.Reflection;
using CrucibleEditor.GUI.Controls.Inspector;
using Crucible;
using CrucibleEditor.Util;

namespace CrucibleEditor.GUI.Controls;

public static class InspectorRenderer
{
    private static Dictionary<Type, object> _renderers = new Dictionary<Type, object>();

    internal static void RegisterRenderer<T>(InspectorComponentView<T> renderer)
    {
        _renderers[typeof(T)] = renderer;

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

            if (ImGUI.CollapsingHeader(title))
            {
                //ImGUI.Label("##Component", title);

                object? componentRenderer;
                if (_renderers.TryGetValue(typeof(T), out componentRenderer))
                {
                    InspectorComponentView<T> compRenderer = (InspectorComponentView<T>) componentRenderer;
                    compRenderer.Draw(ref component);
                }
            }
        }
    }

    public static void DrawMember<T>(string name,ref T component)
    {
        ImGUI.Label(name,component.GetType().Name);
        object? componentView = null;
        if (_renderers.TryGetValue(typeof(T), out componentView))
        {
            InspectorComponentView<T> compRenderer = (InspectorComponentView<T>) componentView;
            compRenderer.Draw(ref component);
        }
        else
        {
            
        }
    }
}
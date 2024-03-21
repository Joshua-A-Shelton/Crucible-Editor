using System.Reflection;
using Avalonia.Controls;
using Avalonia.Controls.Templates;
using Avalonia.Layout;
using Avalonia.Media;
using Crucible;
using CrucibleEditor.Controls.Components;
using CrucibleEditor.Controls.Editors;
using CrucibleEditor.Utils;

namespace CrucibleEditor;

public class ComponentViewLocator: IDataTemplate
{
    private static Dictionary<Type, Type> _componentEditors = new Dictionary<Type, Type>();
    internal static void RegisterEditors()
    {
        var editors = AppDomain.CurrentDomain.GetAssemblies()
            // alternative: .GetExportedTypes()
            .SelectMany(domainAssembly => domainAssembly.GetTypes())
            .Where(type => !type.IsAbstract && type.IsSubClassOfGeneric(typeof(ComponentViewer<>))
                // alternative: => type.IsSubclassOf(typeof(B))
                // alternative: && type != typeof(B)
                // alternative: && ! type.IsAbstract
            ).ToArray();
        foreach (var editor in editors)
        {
            var forType = editor.BaseType.GenericTypeArguments[0];
            _componentEditors[forType] = editor;
        }
    }
    
    public Control? Build(object? param)
    {
        Type? c = null;
        if (_componentEditors.TryGetValue(param.GetType(), out c))
        {
            
            var content = (Control)Activator.CreateInstance(c, new object[]{});
            return content;

        }
        else
        {
            return new TextBlock{ Text = "Unable to present "+param.GetType()};
        }
    }

    public bool Match(object? data)
    {
        return true;
        //return data.GetType().GetCustomAttributes(typeof(ComponentAttribute),false).Length > 0;
    }
}
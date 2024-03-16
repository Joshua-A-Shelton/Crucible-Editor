using System.Reflection;
using Avalonia.Controls;
using Avalonia.Controls.Templates;
using Avalonia.Media;
using Crucible;
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
            .Where(type => !type.IsAbstract && type.IsSubClassOfGeneric(typeof(ComponentEditor<>))
                // alternative: => type.IsSubclassOf(typeof(B))
                // alternative: && type != typeof(B)
                // alternative: && ! type.IsAbstract
            ).ToArray();
        foreach (var editor in editors)
        {
            var forType = editor.GetProperty("Component", BindingFlags.Instance | BindingFlags.Public).PropertyType;
            _componentEditors[forType] = editor;
        }
    }
    
    public Control? Build(object? param)
    {
        Expander ex = new Expander();
        ex.Header = param.GetType().ToString();
        Type? c = null;
        if (_componentEditors.TryGetValue(param.GetType(), out c))
        {
            
            var content = (Control)Activator.CreateInstance(c, new object[]{});
            c.GetMethod("setComponentInit", BindingFlags.Instance | BindingFlags.NonPublic).Invoke(content,new []{param});
            ex.Content = content;

        }
        else
        {
            ex.Content = new TextBlock{ Text = "Unable to present "+param.GetType()};

        }
        return ex;
    }

    public bool Match(object? data)
    {
        return true;
        //return data.GetType().GetCustomAttributes(typeof(ComponentAttribute),false).Length > 0;
    }
}
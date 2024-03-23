using System.Reflection;
using Avalonia.Controls;
using Avalonia.Controls.Templates;
using Avalonia.Data;
using Avalonia.Layout;
using Avalonia.Media;
using Crucible;
using CrucibleEditor.Controls.Editors;
using CrucibleEditor.Utils;
using NP.Utilities;

namespace CrucibleEditor;

public class ComponentViewLocator: IDataTemplate
{
    private static Dictionary<Type, Type> _componentEditors = new Dictionary<Type, Type>();
    public WeakReference<GameObject> GameObject = new WeakReference<GameObject>(null);
    internal static void RegisterEditors()
    {
        var editors = AppDomain.CurrentDomain.GetAssemblies()
            // alternative: .GetExportedTypes()
            .SelectMany(domainAssembly => domainAssembly.GetTypes())
            .Where(type => !type.IsAbstract && type.IsSubClassOfGeneric(typeof(Editor<>))
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
        if (param != null && param.GetType().GetCustomAttributes(typeof(ComponentAttribute), false).Length > 0)
        {
            var members = param.GetType().GetMembers().Where(prop => prop.IsDefined(typeof(ExposeAttribute)));
            StackPanel editorsPanel = new StackPanel();
            editorsPanel.Orientation = Orientation.Vertical;
            foreach (var member in members)
            {
               editorsPanel.Children.Add(getEditor(member));
            }

            return editorsPanel;
        }

        return null;
    }

    private StackPanel getEditor(MemberInfo memberInfo)
    {
        Type forType = memberInfo.GetUnderlyingType();
        string memberName = memberInfo.Name;
        var expose = memberInfo.GetCustomAttribute(typeof(ExposeAttribute)) as ExposeAttribute;
        if (expose != null && !string.IsNullOrEmpty(expose.Name))
        {
            memberName = expose.Name;
        }

        StackPanel stackPanel = new StackPanel();
        stackPanel.Orientation = Orientation.Horizontal;
        TextBlock label = new TextBlock();
        label.Text = memberName;
        stackPanel.Children.Add(label);
        
        Type? c = null;
        if (_componentEditors.TryGetValue(forType, out c))
        {
            var content = (Control)Activator.CreateInstance(c, new object[]{});
            stackPanel.Children.Add(content);
        }
        else
        {
            StackPanel sp = new StackPanel();
            sp.Orientation = Orientation.Vertical;
            var members = forType.GetMembers().Where(prop => prop.IsDefined(typeof(ExposeAttribute)));
            if (members.Count() > 0)
            {
                foreach (var member in members)
                {
                    sp.Children.Add(getEditor(member));
                }
            }
            else
            {
                TextBlock defaultControl = new TextBlock();
                defaultControl.Text = forType.ToString();
                sp.Children.Add(defaultControl);
            }
            stackPanel.Children.Add(sp);
        }

        

        return stackPanel;
    }

    public bool Match(object? data)
    {
        return true;
        //return data.GetType().GetCustomAttributes(typeof(ComponentAttribute),false).Length > 0;
    }
}
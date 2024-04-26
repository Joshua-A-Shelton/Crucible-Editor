using System.Globalization;
using System.Reflection;
using Avalonia.Data;
using Avalonia.Data.Converters;
using Crucible;
using Crucible.Nodes;
using CrucibleEditor.Editors.PropertyControls;
using CrucibleEditor.Utils;

namespace CrucibleEditor.Converters;

public class NodeToPropertiesConverter: IValueConverter
{
    public object? Convert(object? value, Type targetType, object? parameter, CultureInfo culture)
    {
        if (value is Node node)
        {
            List<AbstractPropertyControl> controls = new List<AbstractPropertyControl>();
            var exposed = value.GetType().GetMembers(BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic)
                .Where(prop => prop.IsDefined(typeof(ExposeAttribute), true));
            foreach (var att in exposed)
            {
                AbstractPropertyControl control = PropertyControlRegistry.GetControlFor(att.GetUnderlyingType());
                control.ForObject = node;
                control.ForObjectMember = att;
                if (att is PropertyInfo pi)
                {
                    control.SetEditing(pi.GetValue(node));
                }
                else if (att is FieldInfo fi)
                {
                    control.SetEditing(fi.GetValue(node));
                }
                controls.Add(control);
            }

            return controls;
        }

        return null;
    }

    public object? ConvertBack(object? value, Type targetType, object? parameter, CultureInfo culture)
    {
        throw new NotImplementedException();
    }
}
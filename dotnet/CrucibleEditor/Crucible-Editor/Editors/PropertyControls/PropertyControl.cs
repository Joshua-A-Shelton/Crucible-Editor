using System.Reflection;
using Avalonia;

namespace CrucibleEditor.Editors.PropertyControls;

public class PropertyControl<T>: AbstractPropertyControl
{
    public static readonly StyledProperty<T> EditingProperty =
        AvaloniaProperty.Register<PropertyControl<T>, T>(nameof(Editing));

    public T Editing
    {
        get { return GetValue(EditingProperty); }
        set
        {
            SetValue(EditingProperty, value);
            //structs have to be explicitly assigned again on the parent object
            if (typeof(T).IsValueType)
            {
                if (ForObjectMember is PropertyInfo pi)
                {
                    pi.SetValue(ForObject,value);
                }
                else if (ForObjectMember is FieldInfo fi)
                {
                    fi.SetValue(ForObject,value);
                }
            }
        }
    }

    internal override void SetEditing(object obj)
    {
        Editing = (T)obj;
        DataContext = obj;
    }
}
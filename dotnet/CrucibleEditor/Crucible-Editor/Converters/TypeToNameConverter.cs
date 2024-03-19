using System.Globalization;
using Avalonia.Data.Converters;
using Crucible;

namespace CrucibleEditor.Converters;

public class TypeToNameConverter: IValueConverter
{
    public object? Convert(object? value, Type targetType, object? parameter, CultureInfo culture)
    {
        var comp = value.GetType().GetCustomAttributes(typeof(ComponentAttribute), false).FirstOrDefault() as ComponentAttribute;
        if (comp != null && comp.ExposedName!=null)
        {
            return comp.ExposedName;
        }
        else
        {
            return value.GetType().Name;
        }
    }

    public object? ConvertBack(object? value, Type targetType, object? parameter, CultureInfo culture)
    {
        throw new NotImplementedException();
    }
}
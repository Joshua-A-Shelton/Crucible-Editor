using System.Globalization;
using Avalonia.Data.Converters;
using Crucible;

namespace CrucibleEditor.Converters;

public class GameObjectToPropertiesConverter: IValueConverter
{
    public object? Convert(object? value, Type targetType, object? parameter, CultureInfo culture)
    {
        if (value is GameObject gameObject)
        {
            return gameObject.Components();
        }

        return new object[0];
    }

    public object? ConvertBack(object? value, Type targetType, object? parameter, CultureInfo culture)
    {
        throw new NotImplementedException();
    }
}
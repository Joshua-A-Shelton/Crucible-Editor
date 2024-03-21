using System.Globalization;
using System.Runtime.Intrinsics.X86;
using Avalonia.Data.Converters;
using Crucible;

namespace CrucibleEditor.Converters;

public class Vector3ToStringConverter: IValueConverter
{
    public object? Convert(object? value, Type targetType, object? parameter, CultureInfo culture)
    {
        if (value is Vector3 vec)
        {
            if (parameter != null && parameter is string pString)
            {
                switch (pString)
                {
                    case "X":
                    case "x":
                        return vec.x.ToString();
                    case "Y":
                    case "y":
                        return vec.y.ToString();
                    case "Z":
                    case "z":
                        return vec.z.ToString();;
                    default:
                        return "Unknown parameter " + pString;
                }
            }

            return vec.ToString();
        }

        return "";
    }

    public object? ConvertBack(object? value, Type targetType, object? parameter, CultureInfo culture)
    {
        Console.WriteLine(value);
        if (value is string vectorString)
        {
            var splits = vectorString.Replace("{", "").Replace("}", "").Split(",", StringSplitOptions.TrimEntries);
            float x = float.Parse(splits[0]);
            float y = float.Parse(splits[1]);
            float z = float.Parse(splits[2]);
            return new Vector3(x, y, z);
        }

        return null;
    }
}
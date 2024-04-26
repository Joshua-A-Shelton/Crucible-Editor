using System.Reflection;
using CrucibleEditor.Utils;

namespace CrucibleEditor.Editors.PropertyControls;

public static class PropertyControlRegistry
{
    private static Dictionary<Type, Type> _propertyControls =
        new Dictionary<Type, Type>();

    static PropertyControlRegistry()
    {
        var controlTypes = Assembly.GetExecutingAssembly().GetTypes()
            .Where(t => t.IsSubClassOfGeneric(typeof(PropertyControl<>)) && !t.IsAbstract);
        foreach (var controlType in controlTypes)
        {
            //TODO: this only checks the direct level below, which should be fine in most cases, but if a class extends a class that extends propertyControl, we're in trouble
            RegisterControl(controlType.BaseType.GenericTypeArguments[0],controlType);
        }
    }

    public static void RegisterControl(Type forType, Type controlType)
    {
        if (controlType.IsSubClassOfGeneric(typeof(PropertyControl<>)) && !controlType.IsAbstract)
        {
            Type? exisitingType = null;
            if (_propertyControls.TryGetValue(forType, out exisitingType))
            {
                throw new ArgumentException("Parameter \""+nameof(forType)+"\" of type \""+forType+"\" already has an assigned property control type");
            }

            _propertyControls[forType] = controlType;
        }
        else
        {
            throw new ArgumentException("Parameter \"" + nameof(controlType) + "\" must be a property control type");
        }
    }

    public static AbstractPropertyControl GetControlFor(Type forType)
    {
        Type controlType = _propertyControls[forType];
        AbstractPropertyControl control = (AbstractPropertyControl)(Activator.CreateInstance(controlType));
        return control;
    }
}
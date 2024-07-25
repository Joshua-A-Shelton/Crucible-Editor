using System.Reflection;
using Avalonia;
using Avalonia.Controls;
using Crucible.Nodes;

namespace CrucibleEditor.Editors.PropertyControls;

public abstract class AbstractPropertyControl: UserControl
{
    public static readonly StyledProperty<object> ForObjectProperty =
        AvaloniaProperty.Register<AbstractPropertyControl, object>(nameof(ForObject));

    public object ForObject
    {
        get { return GetValue(ForObjectProperty); }
        set { SetValue(ForObjectProperty, value); }
    }

    public static readonly StyledProperty<MemberInfo> ForObjectMemberProperty =
        AvaloniaProperty.Register<AbstractPropertyControl, MemberInfo>(nameof(ForObjectMember));

    public MemberInfo ForObjectMember
    {
        get { return GetValue(ForObjectMemberProperty); }
        set { SetValue(ForObjectMemberProperty, value); }
    }

    internal abstract void SetEditing(object obj);
}
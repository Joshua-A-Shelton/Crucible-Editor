using Avalonia.Controls;
using Avalonia.Platform;

namespace CrucibleEditor.Controls;

public unsafe class SceneView: NativeControlHost
{
    public IntPtr Handle { get; private set; }
    protected override IPlatformHandle CreateNativeControlCore(IPlatformHandle parent)
    {
        var handle = base.CreateNativeControlCore(parent);
        Handle = _createSceneView(handle.Handle);
        return handle;
    }

    protected override void DestroyNativeControlCore(IPlatformHandle control)
    {
        _destroySceneView(Handle);
        base.DestroyNativeControlCore(control);
    }

    private static delegate* unmanaged<IntPtr,IntPtr> _createSceneView;
    private static delegate* unmanaged<IntPtr,void> _destroySceneView;
    
}
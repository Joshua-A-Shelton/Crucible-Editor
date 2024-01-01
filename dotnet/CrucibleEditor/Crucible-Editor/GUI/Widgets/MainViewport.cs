using Crucible;

namespace CrucibleEditor.GUI.Widgets;

public unsafe class MainViewport:Widget
{
    public MainViewport()
    {
        Title = "Main Viewport";
        CanClose = false;
    }

    private static IntPtr _sceneTexture;
    private static Vector2 _size;
    protected override void Render()
    {
        var size = ImGUI.GetContentRegionAvail();
        if (_size != size)
        {
            _size = size;
            _resizeMainViewportTextures_ptr(_size.x, _size.y);
        }
        ImGUI.Image(_sceneTexture,size,new Vector2(0,0),new Vector2(1,1),new Vector4(1,1,1,1),new Vector4(0,0,0,0));
    }

    private static void SetSceneTexture(IntPtr texture)
    {
        _sceneTexture = texture;
    }

    private static delegate* unmanaged<float, float, void> _resizeMainViewportTextures_ptr;

}
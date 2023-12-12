namespace CrucibleEditor.GUI;

public abstract unsafe class Widget
{
    public string Title { get; protected set; } = "";
    public bool CanClose { get; protected set; } = true;
    protected abstract void Render();

    public void Draw()
    {
        if (CanClose)
        {
             bool isOpen = ImGUI.BeginClosable(Title);
             if (!isOpen)
             {
                 ImGUI.End();
                 return;
             }
        }
        else
        {
            ImGUI.Begin(Title);
        }

        ImGUI.PushFont(ImGUI.FontStyle.Body);
        Render();
        ImGUI.PopFont();
        ImGUI.End();
    }
    
}
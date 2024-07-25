using Avalonia;
using CrucibleEditor.Controls;

namespace CrucibleEditor;

public static class Main
{
    public static void AvaloniaMain()
    {
        try
        {
            string[] args = new string[]{""};
            BuildAvaloniaApp()
                .StartWithClassicDesktopLifetime(args);
        }
        catch (Exception e)
        {
            Console.WriteLine(e);
            throw;
        }
        
    }
    
    // Avalonia configuration, don't remove; also used by visual designer.
    public static AppBuilder BuildAvaloniaApp()
    {
        return AppBuilder.Configure<App>()
            .UsePlatformDetect()
            .WithInterFont()
            .LogToTrace();
    }
}
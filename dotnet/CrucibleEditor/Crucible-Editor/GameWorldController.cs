using System.ComponentModel;
using System.Runtime.CompilerServices;
using Crucible;
using Crucible.Nodes;

namespace CrucibleEditor;

public class GameWorldController: INotifyPropertyChanged
{
    private static GameWorldController _instance = null;

    private GameWorldController()
    {
        
    }

    public static GameWorldController Instance
    {
        get
        {
            if (_instance == null)
            {
                _instance = new GameWorldController();
            }

            return _instance;
        }
    }
    public event PropertyChangedEventHandler PropertyChanged;
    protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
    {
        PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }

    private Node _selectedNode = null;
    public Node SelectedNode
    {
        get
        {
            return _selectedNode;
        }
        set
        {
            _selectedNode = value;
            OnPropertyChanged();
        }
    }
}
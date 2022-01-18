using Lw9.Model;
using System.ComponentModel;
using System.Collections.ObjectModel;
using System.Collections.Specialized;

namespace Lw9.ViewModel
{
    public class ShapeListViewModel : INotifyPropertyChanged
    {
        private CanvasModel _canvasModel;
        private SelectedShapeViewModel _selectedShapeViewModel;
        private ObservableCollection<ShapeViewModel> _shapes = new();
        public event PropertyChangedEventHandler? PropertyChanged;

        public ShapeListViewModel(DocumentModel document, SelectedShapeViewModel selectedShape)
        {
            _selectedShapeViewModel = selectedShape;
            _canvasModel = document.CanvasModel;
            _canvasModel.Shapes.CollectionChanged += HandleCollectionChanged;
        }
        private void HandleCollectionChanged(object? sender, NotifyCollectionChangedEventArgs e)
        {
            if (e.Action == NotifyCollectionChangedAction.Add)
            {
                _shapes.Insert(e.NewStartingIndex, new ShapeViewModel(((ObservableCollection<ShapeModel>)sender!)[e.NewStartingIndex]));
            }

            if (e.Action == NotifyCollectionChangedAction.Remove)
            {
                _shapes.Remove(_shapes[e.OldStartingIndex]);
            }

            if (e.Action == NotifyCollectionChangedAction.Reset)
            {
                _shapes.Clear();
            }
        }
        public SelectedShapeViewModel SelectedShapeVM
        {
            get => _selectedShapeViewModel;
            set
            {
                if (_selectedShapeViewModel == value) return;
                _selectedShapeViewModel = value;
                OnPropertyChanged("SelectedShapeViewModel");
            }
        }
        public ObservableCollection<ShapeViewModel> Shapes
        {
            get => _shapes;
            set => _shapes = value;
        }
        void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}

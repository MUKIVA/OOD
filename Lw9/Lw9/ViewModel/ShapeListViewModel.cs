using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Lw9.Model;
using System.ComponentModel;
using System.Threading.Tasks;
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

        public ShapeListViewModel(CanvasModel canvasModel, SelectedShapeViewModel selectedShape)
        {
            _selectedShapeViewModel = selectedShape;
            _canvasModel = canvasModel;
            _canvasModel.Shapes.CollectionChanged += HandleCollectionChanged;
            _selectedShapeViewModel.PropertyChanged += (s, e) => { if (e.PropertyName == "SelectedShape") OnPropertyChanged("SelectedShape"); };
        }

        private void HandleCollectionChanged(object? sender, NotifyCollectionChangedEventArgs e)
        {
            if (e.Action == NotifyCollectionChangedAction.Add)
            {
                _shapes.Add(new ShapeViewModel(((ObservableCollection<ShapeModel>)sender!)[e.NewStartingIndex]));
            }

            if (e.Action == NotifyCollectionChangedAction.Remove)
            {
                _shapes.Remove(_shapes[e.OldStartingIndex]);
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

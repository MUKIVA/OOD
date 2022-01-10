using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using Lw9.Model;
using System.Collections.ObjectModel;
using System.Windows.Input;
using System.Windows;

namespace Lw9.ViewModel
{
    public class SelectedShapeViewModel : INotifyPropertyChanged
    {
        private ShapeModel? _selectedShape;
        private CanvasModel _canvasModel;
        private ICommand? _resize;

        public event PropertyChangedEventHandler? PropertyChanged;

        public SelectedShapeViewModel(CanvasModel canvasModel)
        {
            _canvasModel = canvasModel;
        }
        public ShapeModel? SelectedShape
        {
            get { return _selectedShape; }
            set
            {
                if (_selectedShape == value) return;
                _selectedShape = value;
                OnPropertyChanged("SelectedShape");
            }
        }
        public ICommand Resize
        {
            get => _resize!;
            set
            {
                if (_resize == value) return;
                _resize = value;
                OnPropertyChanged("Resize");
            }
        }
        public void SetSelectedShapePosition(double x, double y)
        {
            if (_selectedShape == null) return;

            _selectedShape.CanvasLeft = x;
            _selectedShape.CanvasTop = y;
        }
        void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}

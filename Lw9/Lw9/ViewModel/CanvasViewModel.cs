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
using System.Windows.Controls;

namespace Lw9.ViewModel
{
    public class CanvasViewModel : INotifyPropertyChanged, ISelectField
    {
        private CanvasModel _canvasModel;
        private SelectedShapeViewModel _selectedShapeViewModel;
        private ICommand? _resetSelectionShape;
        private ICommand? _selectShape;
        public event PropertyChangedEventHandler? PropertyChanged;
        public CanvasViewModel(CanvasModel canvasModel, SelectedShapeViewModel selectedShapeVM)
        {
            _canvasModel = canvasModel;
            _selectedShapeViewModel = selectedShapeVM;
        }
        public CanvasModel CanvasModel
        {
            get { return _canvasModel; }
        }
        public SelectedShapeViewModel SelectedShapeVM
        {
            get { return _selectedShapeViewModel; }
            set 
            {
                if (_selectedShapeViewModel == value) return;
                _selectedShapeViewModel = value;
                OnPropertyChanged("SelectedShapeViewModel");
            }
        }
        public ICommand SelectShape
        {
            get => _selectShape ?? (_selectShape = new DelegateCommand((shape) => 
            {
                _selectedShapeViewModel.SelectedShape = shape as ShapeModel;
            }));
        }
        public ICommand ResetSelectionShape
        {
            get => _resetSelectionShape ?? (_resetSelectionShape = new DelegateCommand((x) => 
            {
                _selectedShapeViewModel.SelectedShape = null;
            }));
        }
        void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        public void SelectObject(object? obj)
        {
            SelectShape.Execute(obj);
        }
        public void ResetSelect()
        {
            ResetSelectionShape.Execute(null);
        }
        public void SetObjectPosition(double x, double y)
        {
            SelectedShapeVM.SetSelectedShapePosition(x, y);
        }
        public object? GetDraggingObject()
        {
            return SelectedShapeVM.SelectedShape;
        }
    }
}

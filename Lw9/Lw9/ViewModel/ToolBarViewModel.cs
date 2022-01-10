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
    public class ToolBarViewModel
    {
        private CanvasModel _canvasModel;
        private SelectedShapeViewModel _selectedShapeViewModel;
        private ICommand? _addTriangle;
        private ICommand? _addRectangle;
        private ICommand? _addEllipse;
        private ICommand? _deleteShape;

        public ToolBarViewModel(CanvasModel canvasModel, SelectedShapeViewModel selectedShapeVM)
        { 
            _canvasModel = canvasModel;
            _selectedShapeViewModel = selectedShapeVM;
        }

        public ICommand DeleteShape
        {
            get => _deleteShape ?? (_deleteShape = new DelegateCommand(x => 
            {
                _canvasModel.Shapes.Remove(_selectedShapeViewModel.SelectedShape!);
                _selectedShapeViewModel.SelectedShape = null;
            }, (x) => _selectedShapeViewModel.SelectedShape != null));
        }
        public ICommand AddTriangle
        {
            get
            {
                return _addTriangle ?? (_addTriangle = new DelegateCommand(obj =>
                {
                    _canvasModel.Shapes.Add(new ShapeModel(Common.ShapeType.Triangle, 100, 100, 100, 100));
                }));
            }
        }
        public ICommand AddRectangle
        {
            get
            {
                return _addRectangle ?? (_addRectangle = new DelegateCommand(obj =>
                {
                    _canvasModel.Shapes.Add(new ShapeModel(Common.ShapeType.Rectangle, 100, 100, 100, 100));
                }));
            }
        }
        public ICommand AddEllipse
        {
            get
            {
                return _addEllipse ?? (_addEllipse = new DelegateCommand(obj =>
                {
                    _canvasModel.Shapes.Add(new ShapeModel(Common.ShapeType.Ellipse, 100, 100, 100, 100));
                }));
            }
        }
    }
}

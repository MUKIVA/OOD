using System.ComponentModel;
using Lw9.Model;
using Lw9.HistoryService;
using System.Collections.ObjectModel;
using System.Windows.Input;
using System.Collections.Specialized;
using System.Windows.Media.Imaging;
using System.Windows.Media;
using System;
using System.Collections.Generic;

namespace Lw9.ViewModel
{
    public class CanvasViewModel : INotifyPropertyChanged, ISelectField
    {
        private ObservableCollection<ShapeViewModel> _shapes = new();
        private SelectedShapeViewModel _selectedShapeViewModel;
        private ICommand? _resetSelectionShape;
        private ICommand? _selectShape;
        private ICommand? _addTriangle;
        private ICommand? _addRectangle;
        private ICommand? _addEllipse;
        private ICommand? _deleteShape;
        private DocumentModel _document;
        public event PropertyChangedEventHandler? PropertyChanged;
        public CanvasViewModel(SelectedShapeViewModel selectedShapeVM, DocumentModel document)
        {
            _document = document;
            _selectedShapeViewModel = selectedShapeVM;
            document.CanvasModel.PropertyChanged += (s, e) => { if (e.PropertyName == "Width") OnPropertyChanged("Width");             };
            document.CanvasModel.PropertyChanged += (s, e) => { if (e.PropertyName == "Height") OnPropertyChanged("Height");           };
            document.CanvasModel.PropertyChanged += (s, e) => { if (e.PropertyName == "PicturePath") OnPropertyChanged("ImageSource"); };
            document.CanvasModel.Shapes.CollectionChanged += HandleCollectionChanged;
        }
        public string? PicturePath
        {
            get => _document.CanvasModel.PicturePath;
            set => _document.CanvasModel.PicturePath = value;
        }
        public BitmapSource ImageSource
        {
            get
            {
                if (_document.CanvasModel.PicturePath == null)
                    return BitmapImage.Create(1, 1, 1, 1, PixelFormats.BlackWhite, null, new byte[] { 255 }, 1);

                var image = new BitmapImage();
                image.BeginInit();
                image.UriSource = new Uri(Environment.CurrentDirectory + _document.CanvasModel.PicturePath);
                image.EndInit();
                
                byte[] pixels = new byte[image.PixelHeight * image.PixelWidth * 4];
                image.CopyPixels(pixels, image.PixelWidth * 4, 0);
                return BitmapImage.Create(
                    image.PixelWidth, 
                    image.PixelHeight, 
                    image.DpiX,
                    image.DpiY,
                    image.Format,
                    image.Palette,
                    pixels, image.PixelWidth * 4);
            }
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
                _selectedShapeViewModel.SelectedShape = shape as ShapeViewModel;
            }));
        }
        public ICommand ResetSelectionShape
        {
            get => _resetSelectionShape ?? (_resetSelectionShape = new DelegateCommand((x) => 
            {
                _selectedShapeViewModel.SelectedShape = null;
            }));
        }
        public void SelectObject(object? obj)
        {
            SelectShape.Execute(obj);
        }
        public void ResetSelect()
        {
            ResetSelectionShape.Execute(null);
        }
        public object? GetSelectObject()
        {
            return SelectedShapeVM.SelectedShape;
        }
        public ObservableCollection<ShapeViewModel> Shapes
        {
            get => _shapes;
            set => _shapes = value;
        }
        public int Height
        {
            get => _document.CanvasModel.Height;
            set => _document.CanvasModel.Height = value;
        }
        public int Width
        {
            get => _document.CanvasModel.Width;
            set => _document.CanvasModel.Width = value;
        }
        public ICommand DeleteShape
        {
            get => _deleteShape ?? (_deleteShape = new DelegateCommand(x =>
            {
                if (SelectedShapeVM.SelectedShape == null) return;
                int index = _shapes.IndexOf(SelectedShapeVM.SelectedShape);
                if (_document != null)
                    _document?.History?.AddToHistory(new DeleteShapeCommand(_document.CanvasModel, index));
                else
                    _document?.CanvasModel.Shapes.Remove(_document.CanvasModel.Shapes[index]);
                _selectedShapeViewModel.SelectedShape = null;

            }, (x) => _selectedShapeViewModel.SelectedShape != null));
        }
        public ICommand AddTriangle
        {
            get
            {
                return _addTriangle ?? (_addTriangle = new DelegateCommand(obj =>
                {
                    if (_document != null)
                    {
                        _document?.History?.AddToHistory(new CreateShapeCommand(
                            _document.CanvasModel, new ShapeModel(Common.ShapeType.Triangle, 100, 100, 100, 100), SelectedShapeVM));
                    }
                    else
                    {
                        _document?.CanvasModel.Shapes.Add(new ShapeModel(Common.ShapeType.Triangle, 100, 100, 100, 100));
                    }
                }));
            }
        }
        public ICommand AddRectangle
        {
            get
            {
                return _addRectangle ?? (_addRectangle = new DelegateCommand(obj =>
                {
                    if (_document != null)
                    {
                        _document?.History?.AddToHistory(new CreateShapeCommand(
                            _document.CanvasModel, new ShapeModel(Common.ShapeType.Rectangle, 100, 100, 100, 100), SelectedShapeVM));
                    }
                    else
                    {
                        _document?.CanvasModel.Shapes.Add(new ShapeModel(Common.ShapeType.Rectangle, 100, 100, 100, 100));
                    }
                }));
            }
        }
        public ICommand AddEllipse
        {
            get
            {
                return _addEllipse ?? (_addEllipse = new DelegateCommand(obj =>
                {
                    if (_document != null)
                    {
                        _document?.History?.AddToHistory(new CreateShapeCommand(
                            _document.CanvasModel, new ShapeModel(Common.ShapeType.Ellipse, 100, 100, 100, 100), SelectedShapeVM));
                    }
                    else
                    {
                        _document?.CanvasModel.Shapes.Add(new ShapeModel(Common.ShapeType.Ellipse, 100, 100, 100, 100));
                    }
                }));
            }
        }
        private void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        

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
    }
}

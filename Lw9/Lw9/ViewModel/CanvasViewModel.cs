﻿using System.ComponentModel;
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
        
        private CanvasModel _canvasModel;
        private ObservableCollection<ShapeViewModel> _shapes = new();
        private SelectedShapeViewModel _selectedShapeViewModel;
        private ICommand? _resetSelectionShape;
        private ICommand? _selectShape;
        private ICommand? _addTriangle;
        private ICommand? _addRectangle;
        private ICommand? _addEllipse;
        private ICommand? _deleteShape;
        private History? _history;
        public event PropertyChangedEventHandler? PropertyChanged;
        public CanvasViewModel(CanvasModel canvasModel, SelectedShapeViewModel selectedShapeVM, History? history = null)
        {
            _history = history;
            _canvasModel = canvasModel;
            _selectedShapeViewModel = selectedShapeVM;
            _canvasModel.PropertyChanged += (s, e) => { if (e.PropertyName == "Width") OnPropertyChanged("Width");             };
            _canvasModel.PropertyChanged += (s, e) => { if (e.PropertyName == "Height") OnPropertyChanged("Height");           };
            _canvasModel.PropertyChanged += (s, e) => { if (e.PropertyName == "PicturePath") OnPropertyChanged("ImageSource"); };
            _canvasModel.Shapes.CollectionChanged += HandleCollectionChanged;
        }
        public string? PicturePath
        {
            get => _canvasModel.PicturePath;
            set => _canvasModel.PicturePath = value;
        }
        public BitmapSource ImageSource
        {
            get
            {
                if (_canvasModel.PicturePath == null)
                    return BitmapImage.Create(1, 1, 1, 1, PixelFormats.BlackWhite, null, new byte[] { 255 }, 1);

                var image = new BitmapImage();
                image.BeginInit();
                image.UriSource = new Uri(Environment.CurrentDirectory + _canvasModel.PicturePath);
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
            get => _canvasModel.Height;
            set => _canvasModel.Height = value;
        }
        public int Width
        {
            get => _canvasModel.Width;
            set => _canvasModel.Width = value;
        }
        public ICommand DeleteShape
        {
            get => _deleteShape ?? (_deleteShape = new DelegateCommand(x =>
            {
                if (SelectedShapeVM.SelectedShape == null) return;
                int index = _shapes.IndexOf(SelectedShapeVM.SelectedShape);
                if (_history != null)
                    _history?.AddToHistory(new DeleteShapeCommand(_canvasModel, index));
                else
                    _canvasModel.Shapes.Remove(_canvasModel.Shapes[index]);
                _selectedShapeViewModel.SelectedShape = null;

            }, (x) => _selectedShapeViewModel.SelectedShape != null));
        }
        public ICommand AddTriangle
        {
            get
            {
                return _addTriangle ?? (_addTriangle = new DelegateCommand(obj =>
                {
                    if (_history != null)
                    {
                        _history?.AddToHistory(new CreateShapeCommand(
                            _canvasModel, new ShapeModel(Common.ShapeType.Triangle, 100, 100, 100, 100), SelectedShapeVM));
                    }
                    else
                    {
                        _canvasModel.Shapes.Add(new ShapeModel(Common.ShapeType.Triangle, 100, 100, 100, 100));
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
                    if (_history != null)
                    {
                        _history?.AddToHistory(new CreateShapeCommand(
                            _canvasModel, new ShapeModel(Common.ShapeType.Rectangle, 100, 100, 100, 100), SelectedShapeVM));
                    }
                    else
                    {
                        _canvasModel.Shapes.Add(new ShapeModel(Common.ShapeType.Rectangle, 100, 100, 100, 100));
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
                    if (_history != null)
                    {
                        _history?.AddToHistory(new CreateShapeCommand(
                            _canvasModel, new ShapeModel(Common.ShapeType.Ellipse, 100, 100, 100, 100), SelectedShapeVM));
                    }
                    else
                    {
                        _canvasModel.Shapes.Add(new ShapeModel(Common.ShapeType.Ellipse, 100, 100, 100, 100));
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

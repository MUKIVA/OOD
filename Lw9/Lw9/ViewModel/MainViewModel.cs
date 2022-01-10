using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using Lw9.Model;
using Lw9.DialogService;
using System.Collections.ObjectModel;
using System.Windows.Input;
using System.Windows;
using System.IO;

namespace Lw9.ViewModel
{
    public class MainViewModel : INotifyPropertyChanged
    {
        private CanvasViewModel _canvas;
        private ToolBarViewModel _toolBar;
        private string _lastSavePath = string.Empty;
        private ICommand? _saveFileCanvasData;
        private ICommand? _saveAsFileCanvasData;
        private ICommand? _openFile;
        private IFileService _fileService = new JsonFileService();
        private IDialogService _dialogService = new DefaultDialogService();
        public event PropertyChangedEventHandler? PropertyChanged;

        public MainViewModel()
        {
            CanvasModel canvasModel = new();
            SelectedShapeViewModel selectedShapeVM = new(canvasModel);
            _canvas = new CanvasViewModel(canvasModel, selectedShapeVM);
            _toolBar = new ToolBarViewModel(canvasModel, selectedShapeVM);
        }
        public CanvasViewModel CanvasVM
        {
            get { return _canvas; }
            set
            {
                if (_canvas == value) return;
                _canvas = value;
                OnPropertyChanged("Canvas");

            }
        }
        public ICommand SaveAsFileCanvasData
        {
            get => _saveAsFileCanvasData ?? (_saveAsFileCanvasData = new DelegateCommand(x => 
            {
                try
                {
                    var data = CanvasVM.CanvasModel.Shapes;
                    if (_dialogService.SaveFileDialog())
                    {
                        _fileService.Save(_dialogService.FilePath, data.ToList());
                        _dialogService.ShowMessage("Файл сохранен");
                        _lastSavePath = _dialogService.FilePath;
                    }
                }
                catch (Exception ex)
                {
                    _dialogService.ShowMessage(ex.Message);
                }      
            }));
        }
        public ICommand SaveFileCanvasData
        {
            get => _saveFileCanvasData ?? (_saveFileCanvasData = new DelegateCommand(x =>
            {
                if (_lastSavePath == string.Empty || !File.Exists(_lastSavePath))
                {
                    SaveAsFileCanvasData.Execute(x);
                    return;
                }

                var data = CanvasVM.CanvasModel.Shapes;
                _fileService.Save(_lastSavePath, data.ToList());

            }));
        }
        public ICommand OpenFile
        {
            get => _openFile ?? (_openFile = new DelegateCommand(x =>
            {
                try
                {
                    if (_dialogService.OpenFileDialog())
                    {
                        CanvasVM.CanvasModel.Shapes.Clear();
                        var fileShapesData = _fileService.Open(_dialogService.FilePath);
                        foreach (ShapeModel shape in fileShapesData)
                        {
                            CanvasVM.CanvasModel.Shapes.Add(shape);
                        }
                        _dialogService.ShowMessage("Файл открыт");
                    }
                }
                catch(Exception ex)
                {
                    _dialogService.ShowMessage(ex.Message);
                }

            }));
        }
        public ToolBarViewModel ToolBarVM
        {
            get { return _toolBar; }
            set
            {
                if (_toolBar == value) return;
                _toolBar = value;
                OnPropertyChanged("ToolBar");
            }
        }
        void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
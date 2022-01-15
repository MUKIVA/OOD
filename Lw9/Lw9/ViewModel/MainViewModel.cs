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
using Lw9.HistoryService;
using System.IO;

namespace Lw9.ViewModel
{
    public class MainViewModel : INotifyPropertyChanged
    {
        private CanvasViewModel _canvasVM;
        private ShapeListViewModel _shapeListViewModel;
        private CanvasModel _canvasModel;
        private string _lastSavePath = string.Empty;
        private ICommand? _saveFileCanvasData;
        private ICommand? _saveAsFileCanvasData;
        private ICommand? _openFile;
        private History _historyService = new History();
        private IFileService<ShapeModel> _fileService = new JsonFileService();
        private IDialogService _dialogService = new DefaultDialogService();
        public event PropertyChangedEventHandler? PropertyChanged;

        public MainViewModel()
        {
            _canvasModel = new();
            SelectedShapeViewModel selectedShapeVM = new(_historyService);
            _shapeListViewModel = new ShapeListViewModel(_canvasModel, selectedShapeVM);
            _canvasVM = new CanvasViewModel(_canvasModel, selectedShapeVM, _historyService);
        }
        public CanvasViewModel CanvasVM
        {
            get { return _canvasVM; }
            set
            {
                if (_canvasVM == value) return;
                _canvasVM = value;
                OnPropertyChanged("Canvas");
            }
        }

        public ShapeListViewModel ShapeInfoVM
        {
            get => _shapeListViewModel;
            set => _shapeListViewModel = value;
        }
        public ICommand SaveAsFileCanvasData
        {
            get => _saveAsFileCanvasData ?? (_saveAsFileCanvasData = new DelegateCommand(x => 
            {
                try
                {
                    var data = _canvasModel.Shapes;
                    if (_dialogService.SaveFileDialog())
                    {
                        _fileService.SaveCollection(_dialogService.FilePath, data.ToList());
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

                var data = _canvasModel.Shapes;
                _fileService.SaveCollection(_lastSavePath, data.ToList());
                _dialogService.ShowMessage("Файл сохранен");

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
                        _canvasVM.Shapes.Clear();
                        _canvasModel.Shapes.Clear();
                        _shapeListViewModel.Shapes.Clear();
                        var fileShapesData = _fileService.OpenCollection(_dialogService.FilePath);
                        foreach (ShapeModel shape in fileShapesData)
                        {
                            _canvasModel.Shapes.Add(shape);
                        }
                        CanvasVM.ResetSelect();
                        _dialogService.ShowMessage("Файл открыт");
                        _historyService.ClearHistory();
                    }
                }
                catch(Exception ex)
                {
                    _dialogService.ShowMessage(ex.Message);
                }

            }));
        }
        public History History
        {
            get => _historyService;
            set
            {
                if (_historyService == value) return;
                _historyService = value;
                OnPropertyChanged("History");   
            }
        }
        void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
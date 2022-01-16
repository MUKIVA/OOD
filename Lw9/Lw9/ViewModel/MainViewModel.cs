using System;
using System.Linq;
using System.ComponentModel;
using Lw9.Model;
using Lw9.DialogService;
using System.Windows.Input;
using Lw9.HistoryService;
using System.IO;

namespace Lw9.ViewModel
{
    public class MainViewModel : INotifyPropertyChanged
    {
        private const string IMAGE_FOLDER = @"\img\";
        private const string TEMP_FOLDER = @"\tmp\";
        private CanvasViewModel _canvasVM;
        private ShapeListViewModel _shapeListViewModel;
        private CanvasModel _canvasModel;
        private string _lastSavePath = string.Empty;
        private ICommand? _saveFileCanvasData;
        private ICommand? _saveAsFileCanvasData;
        private ICommand? _openFile;
        private ICommand? _insertBackground;
        private ICommand? _resetBackground;
        private History _historyService = new History();
        private IFileServiceObj<CanvasModel> _fileService = new JsonFileService();
        private IDialogService _dialogService = new DefaultDialogService();
        public event PropertyChangedEventHandler? PropertyChanged;

        private void CopyDir(string from, string to)
        {
            Directory.CreateDirectory(to);
            foreach (string file in Directory.GetFiles(from))
            { 
                string pathForFile = to + "\\" + Path.GetFileName(file);
                File.Copy(file, pathForFile, true);
            }
        }
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
                    var data = _canvasModel;
                    if (_dialogService.SaveFileDialog())
                    {
                        string saveImageFolder = Path.GetDirectoryName(_dialogService.FilePath) + IMAGE_FOLDER;
                        Directory.CreateDirectory(saveImageFolder);
                        CopyDir(Environment.CurrentDirectory + IMAGE_FOLDER, saveImageFolder);
                        _fileService.Save(_dialogService.FilePath, data);
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

                string saveImageFolder = Path.GetDirectoryName(_dialogService.FilePath) + IMAGE_FOLDER;
                Directory.CreateDirectory(saveImageFolder);
                CopyDir(Environment.CurrentDirectory + IMAGE_FOLDER, saveImageFolder);
                var data = _canvasModel;
                _fileService.Save(_lastSavePath, data);
                _dialogService.ShowMessage("Файл сохранен");

            }));
        }
        public ICommand OpenFile
        {
            get => _openFile ?? (_openFile = new DelegateCommand(x =>
            {
                GC.Collect();
                string? oldPicture = _canvasModel.PicturePath;
                try
                {
                    if (_dialogService.OpenFileDialog("Files|*.json;"))
                    {
                        var fileData = _fileService.Open(_dialogService.FilePath);

                        string openFileDirectory = Path.GetDirectoryName(_dialogService.FilePath)!;
                        if (fileData.PicturePath == oldPicture)
                        {
                            Directory.CreateDirectory(Environment.CurrentDirectory + TEMP_FOLDER);
                            File.Copy(
                                Environment.CurrentDirectory + _canvasModel.PicturePath,
                                Environment.CurrentDirectory + TEMP_FOLDER + Path.GetFileName(_canvasModel.PicturePath), true);
                        }
                        if (!Directory.Exists(openFileDirectory + IMAGE_FOLDER)) 
                            throw new Exception($"Не удалось найти папку \"{IMAGE_FOLDER}\"");
                        if (!File.Exists(openFileDirectory + fileData.PicturePath))
                            throw new Exception($"не удалось найти файл \"{fileData.PicturePath}\"");

                        _canvasModel.Shapes.Clear();
                        _canvasModel.Height = fileData.Height;
                        _canvasModel.Width = fileData.Width;
                        _historyService.ClearHistory();
                        CopyDir(openFileDirectory + IMAGE_FOLDER, Environment.CurrentDirectory + IMAGE_FOLDER);
                        _canvasModel.PicturePath = fileData.PicturePath;
                        foreach (ShapeModel shape in fileData.Shapes)
                        {
                            _canvasModel.Shapes.Add(shape);
                        }
                        CanvasVM.ResetSelect();
                        _dialogService.ShowMessage("Файл открыт");
                    }
                }
                catch(Exception ex)
                {
                    if (_canvasModel.PicturePath != null)
                        File.Copy(
                            Environment.CurrentDirectory + TEMP_FOLDER + Path.GetFileName(_canvasModel.PicturePath), 
                            Environment.CurrentDirectory + _canvasModel.PicturePath, true);
                    _canvasModel.PicturePath = oldPicture;
                    _dialogService.ShowMessage(ex.Message);
                }

            }));
        }
        public ICommand InsertBackground
        {
            get => _insertBackground ?? (_insertBackground = new DelegateCommand(s =>
            {
                try
                {
                    if (_dialogService.OpenFileDialog("Files|*.jpg;*.png;"))
                    {
                        string filePath = _dialogService.FilePath;
                        File.Copy(filePath, Environment.CurrentDirectory + IMAGE_FOLDER + _dialogService.FileName, true);
                        _historyService.AddToHistory(
                            new ChangeBackgroundCommand(_canvasModel, IMAGE_FOLDER + _dialogService.FileName));
                    }
                }
                catch (Exception ex)
                {
                    _dialogService.ShowMessage(ex.Message);
                }
            }));
        }
        public ICommand ResetBackground
        {
            get => _resetBackground ?? (_resetBackground = new DelegateCommand(s =>
            {
                _historyService.AddToHistory(new ChangeBackgroundCommand(_canvasModel, null));
            }, s => _canvasModel.PicturePath != null));
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
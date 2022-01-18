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
        private DocumentModel _documentModel;
        private string _lastSavePath = string.Empty;
        private ICommand? _saveFileCanvasData;
        private ICommand? _saveAsFileCanvasData;
        private ICommand? _openFile;
        private ICommand? _insertBackground;
        private ICommand? _resetBackground;
        private ICommand? _undo;
        private ICommand? _redo;
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
            _documentModel = new DocumentModel(new History(), new CanvasModel());

            SelectedShapeViewModel selectedShapeVM = new(_documentModel);
            _shapeListViewModel = new ShapeListViewModel(_documentModel, selectedShapeVM);
            _canvasVM = new CanvasViewModel(selectedShapeVM, _documentModel);
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
                    var data = _documentModel.CanvasModel;
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
                var data = _documentModel.CanvasModel;
                _fileService.Save(_lastSavePath, data);
                _dialogService.ShowMessage("Файл сохранен");

            }));
        }
        public ICommand OpenFile
        {
            get => _openFile ?? (_openFile = new DelegateCommand(x =>
            {
                GC.Collect();
                string? oldPicture = _documentModel.CanvasModel.PicturePath;
                try
                {
                    if (_dialogService.OpenFileDialog("Files|*.json;"))
                    {
                        var fileData = _fileService.Open(_dialogService.FilePath);

                        string openFileDirectory = Path.GetDirectoryName(_dialogService.FilePath)!;
                        if (fileData.PicturePath == oldPicture && oldPicture != null)
                        {
                            Directory.CreateDirectory(Environment.CurrentDirectory + TEMP_FOLDER);
                            File.Copy(
                                Environment.CurrentDirectory + _documentModel.CanvasModel.PicturePath,
                                Environment.CurrentDirectory + TEMP_FOLDER + Path.GetFileName(_documentModel.CanvasModel.PicturePath), true);
                        }
                        if (!Directory.Exists(openFileDirectory + IMAGE_FOLDER)) 
                            throw new Exception($"Не удалось найти папку \"{IMAGE_FOLDER}\"");
                        if (!File.Exists(openFileDirectory + fileData.PicturePath) && fileData.PicturePath != null)
                            throw new Exception($"не удалось найти файл \"{fileData.PicturePath}\"");

                        _documentModel.CanvasModel.Shapes.Clear();
                        _documentModel.CanvasModel.Height = fileData.Height;
                        _documentModel.CanvasModel.Width = fileData.Width;
                        _documentModel?.History?.ClearHistory();
                        CopyDir(openFileDirectory + IMAGE_FOLDER, Environment.CurrentDirectory + IMAGE_FOLDER);
                        _documentModel!.CanvasModel.PicturePath = fileData.PicturePath;
                        foreach (ShapeModel shape in fileData.Shapes)
                        {
                            _documentModel.CanvasModel.Shapes.Add(shape);
                        }
                        CanvasVM.ResetSelect();
                        _dialogService.ShowMessage("Файл открыт");
                    }
                }
                catch(Exception ex)
                {
                    if (_documentModel.CanvasModel.PicturePath != null)
                        File.Copy(
                            Environment.CurrentDirectory + TEMP_FOLDER + Path.GetFileName(_documentModel.CanvasModel.PicturePath), 
                            Environment.CurrentDirectory + _documentModel.CanvasModel.PicturePath, true);
                    _documentModel.CanvasModel.PicturePath = oldPicture;
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
                        _documentModel?.History?.AddToHistory(
                            new ChangeBackgroundCommand(_documentModel.CanvasModel, IMAGE_FOLDER + _dialogService.FileName));
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
                _documentModel?.History?.AddToHistory(new ChangeBackgroundCommand(_documentModel.CanvasModel, null));
            }, s => _documentModel.CanvasModel.PicturePath != null));
        }
        public ICommand Undo
        {
            get => _undo ?? (_undo = new DelegateCommand(obj =>
            {
                _documentModel.History!.Undo();
            }, obj => _documentModel.History!.CanUndo()));
        }
        public ICommand Redo
        {
            get => _redo ?? (_redo = new DelegateCommand(obj =>
            {
                _documentModel.History!.Redo();
            }, obj => _documentModel.History!.CanRedo()));
        }
        void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}
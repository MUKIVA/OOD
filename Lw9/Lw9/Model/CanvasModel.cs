using System.ComponentModel;
using System.Collections.ObjectModel;
using System.Windows.Media;
using System;
using System.Windows.Media.Imaging;

namespace Lw9.Model
{
    public class CanvasModel : INotifyPropertyChanged
    {
        private ObservableCollection<ShapeModel> _shapes = new();
        private string? _picturePath = null;
        private int _height;
        private int _width;
        public event PropertyChangedEventHandler? PropertyChanged;

        public string? PicturePath
        {
            get => _picturePath;
            set
            {
                if (value == _picturePath) return;
                _picturePath = value;
                OnPropertyChanged("PicturePath");
            }
        }
        public CanvasModel()
        {
            _height = 480;
            _width = 640;
        }
        public ObservableCollection<ShapeModel> Shapes
        {
            get { return _shapes; }
        }
        public int Height
        {
            get { return _height; }
            set
            {
                if (_height == value) return;
                _height = value;
                OnPropertyChanged("Height");
            }
        }
        public int Width
        {
            get { return _width; }
            set 
            {
                if (_width == value) return;
                _width = value;
                OnPropertyChanged("Width");
            }
        }

        void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}

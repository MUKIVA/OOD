using Lw9.Common;
using System.ComponentModel;

namespace Lw9.Model
{
    public class ShapeModel : INotifyPropertyChanged
    {
        private double _width;
        private double _height;
        private double _canvasLeft;
        private double _canvasTop;
        private ShapeType _shapeType;
        public event PropertyChangedEventHandler? PropertyChanged;

        public ShapeType ShapeType
        {
            get { return _shapeType; }
            set 
            { 
                _shapeType = value;
            }
        }
        public double Width
        {
            get { return _width; }
            set
            {
                if (_width == value) return;
                _width = value;
                OnPropertyChanged("Width");
            }
        }
        public double Height
        {
            get { return _height; }
            set
            {
                if (_height == value) return;
                _height = value;
                OnPropertyChanged("Height");
            }
        }
        public double CanvasLeft
        {
            get { return _canvasLeft; }
            set
            {
                if (_canvasLeft == value) return;
                _canvasLeft = value;
                OnPropertyChanged("CanvasLeft");
            }
        }
        public double CanvasTop
        {
            get { return _canvasTop; }
            set
            {
                if (value == _canvasTop) return;
                _canvasTop = value;
                OnPropertyChanged("CanvasTop");
            }
        }
        public ShapeModel(ShapeType type, double width, double height, double left, double top) 
            => (_shapeType, _width, _height, _canvasLeft, _canvasTop) 
             = (type,       width,  height,  left,        top);
        public ShapeModel() {}
        void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}

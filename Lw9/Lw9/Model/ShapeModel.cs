using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lw9.Common;
using System.Runtime.Serialization;
using System.ComponentModel;
using System.Windows.Media;
using Lw9.HistoryService;
using System.Windows.Shapes;

namespace Lw9.Model
{
    public class ShapeModel : INotifyPropertyChanged
    {
        private double _width;
        private double _height;
        private double _canvasLeft;
        private double _canvasTop;
        private ShapeType _shapeType;
        private HistoryService.HistoryService _history;

        private PointCollection GetPointCollection()
        {
            PointCollection points = new PointCollection();
            points.Add(new System.Windows.Point(0, _height));
            points.Add(new System.Windows.Point(_width, _height));
            points.Add(new System.Windows.Point(_width / 2, 0));
            return points;
        }

        public PointCollection Points
        {
            get => GetPointCollection();
            set
            {
                OnPropertyChanged("Points");
            }
        }

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
                Points = null!;
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
                Points = null!;
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
        public ShapeModel()
        {
            
        }

        public event PropertyChangedEventHandler? PropertyChanged;
        void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}

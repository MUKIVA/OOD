using Lw9.Model;
using Lw9.Common;
using System.ComponentModel;

namespace Lw9.ViewModel
{
    public class ShapeViewModel : INotifyPropertyChanged
    {
        private ShapeModel? _model = new ShapeModel();
        public event PropertyChangedEventHandler? PropertyChanged;

        public ShapeViewModel(ShapeModel? shape)
        {
            _model = shape;

            if (_model == null) return;

            _model.PropertyChanged += (s, e) => { if (e.PropertyName == "Width") OnPropertyChanged("Width"); };
            _model.PropertyChanged += (s, e) => { if (e.PropertyName == "Height") OnPropertyChanged("Height"); };
            _model.PropertyChanged += (s, e) => { if (e.PropertyName == "CanvasTop") OnPropertyChanged("CanvasTop"); };
            _model.PropertyChanged += (s, e) => { if (e.PropertyName == "CanvasLeft") OnPropertyChanged("CanvasLeft"); };
            _model.PropertyChanged += (s, e) => { if (e.PropertyName == "Points") OnPropertyChanged("Points"); };
        }
        public double Width
        {
            get => _model!.Width;
            set => _model!.Width = value;
        }
        public double Height
        {
            get => _model!.Height;
            set => _model!.Height = value;
        }
        public double CanvasTop
        {
            get => _model!.CanvasTop;
            set => _model!.CanvasTop = value;
        }
        public double CanvasLeft
        {
            get => _model!.CanvasLeft;
            set => _model!.CanvasLeft = value;
        }
        public ShapeType ShapeType
        {
            get => _model!.ShapeType;
            set => _model!.ShapeType = value;
        }
        
        void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}

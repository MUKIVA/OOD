using Lw9.ViewModel;
using System.Windows;

namespace Lw9.HistoryService
{
    public class ChangeFrameCommand : IUnduableCommand
    {
        private ShapeViewModel _shape;
        private Point _position;
        private double _width;
        private double _height;
        private Point _oldPosition;
        private double _oldWidth;
        private double _oldHeight;

        public ChangeFrameCommand(ShapeViewModel shape, Point oldPosition, double oldHeight, double oldWidth)
        {
            _shape = shape;
            _oldHeight = oldHeight;
            _oldWidth = oldWidth;
            _oldPosition = oldPosition;
            _width = _shape.Width;
            _height = _shape.Height;
            _position = new Point(_shape.CanvasLeft, _shape.CanvasTop);
        }

        public void Execute()
        {
            _shape.Height = _height;
            _shape.Width = _width;
            _shape.CanvasLeft = _position.X;
            _shape.CanvasTop = _position.Y;
        }

        public void Unexecute()
        {
            _shape.Height = _oldHeight;
            _shape.Width = _oldWidth;
            _shape.CanvasLeft = _oldPosition.X;
            _shape.CanvasTop = _oldPosition.Y;
        }
    }
}

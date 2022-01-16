using Lw9.Model;

namespace Lw9.HistoryService
{
    public class DeleteShapeCommand : IUnduableCommand
    {
        private CanvasModel _canvasModel;
        private ShapeModel _shapeModel;
        private int _index;

        public DeleteShapeCommand(CanvasModel canvas, int index)
        {
            _canvasModel = canvas;
            _index = index;
            _shapeModel = _canvasModel.Shapes[_index]; //new ShapeModel(shape.ShapeType, shape.Width, shape.Height, shape.CanvasLeft, shape.CanvasTop);
        }

        public void Execute()
        {
            _canvasModel.Shapes.Remove(_shapeModel);
        }

        public void Unexecute()
        {
            _canvasModel.Shapes.Insert(_index, _shapeModel);
        }
    }
}

using Lw9.Model;
using Lw9.ViewModel;

namespace Lw9.HistoryService
{
    public class CreateShapeCommand : IUnduableCommand
    {

        private CanvasModel _canvasModel;
        private ShapeModel _shapeModel;
        private SelectedShapeViewModel _selectedShape;

        public CreateShapeCommand(CanvasModel canvas, ShapeModel shape, SelectedShapeViewModel selectedShape)
        {
            _shapeModel = shape;
            _canvasModel = canvas;
            _selectedShape = selectedShape;
        }

        public void Execute()
        {
            _canvasModel.Shapes.Add(_shapeModel);
        }

        public void Unexecute()
        {
            _canvasModel.Shapes.Remove(_shapeModel);
            _selectedShape.SelectedShape = null;
        }
    }
}

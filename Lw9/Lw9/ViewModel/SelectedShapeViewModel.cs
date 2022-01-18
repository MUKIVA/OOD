using System.ComponentModel;
using Lw9.HistoryService;
using Lw9.Model;
using System.Windows.Input;

namespace Lw9.ViewModel
{
    public class SelectedShapeViewModel : INotifyPropertyChanged
    {
        private ShapeViewModel? _selectedShape;
        public event PropertyChangedEventHandler? PropertyChanged;
        private DocumentModel? _document;
        private ICommand? _savePosition;
        private ICommand? _saveResize;


        public SelectedShapeViewModel(DocumentModel? historyService = null)
        {
            _document = historyService;
        }

        public ShapeViewModel? SelectedShape
        {
            get { return _selectedShape; }
            set
            {
                if (_selectedShape == value) return;
                _selectedShape = value;
                OnPropertyChanged("SelectedShape");
            }
        }
        public ICommand? SavePosition
        {
            get => _savePosition ?? (_savePosition = new DelegateCommand(positionArgs =>
            {
                var args = (DragDropEventArgs)positionArgs!;

                if (args.OldPos.X == SelectedShape?.CanvasLeft && args.OldPos.Y == SelectedShape.CanvasTop) return;

                 _document?.History?.AddToHistory(
                    new ChangeFrameCommand(
                        SelectedShape!,
                        args.OldPos,
                        SelectedShape!.Height,
                        SelectedShape!.Width));
            }));
        }
        public ICommand? SaveResize
        {
            get => _saveResize ?? (_saveResize = new DelegateCommand(positionArgs =>
            {
                var args = (ResizeEventArgs)positionArgs!;

                if (args.OldPos.X == SelectedShape?.CanvasLeft
                && args.OldPos.Y == SelectedShape.CanvasTop
                && args.OldHeight == SelectedShape.Height
                && args.OldWidth == SelectedShape.Width) return;

                _document?.History?.AddToHistory(
                    new ChangeFrameCommand(
                        SelectedShape!,
                        args.OldPos,
                        args.OldHeight,
                        args.OldWidth));
            }));
        }
        void OnPropertyChanged(string propertyName) => PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
    }
}

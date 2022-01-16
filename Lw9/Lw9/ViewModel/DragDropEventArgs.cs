using System.Windows;

namespace Lw9.ViewModel
{
    public class DragDropEventArgs
    {
        public Point OldPos { get; set; }
        public DragDropEventArgs(Point Old) => (OldPos) = (Old);
    }
}

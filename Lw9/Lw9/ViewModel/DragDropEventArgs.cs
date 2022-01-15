using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Lw9.ViewModel
{
    public class DragDropEventArgs
    {
        public Point OldPos { get; set; }
        public DragDropEventArgs(Point Old) => (OldPos) = (Old);
    }
}

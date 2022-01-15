using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace Lw9.ViewModel
{
    public class ResizeEventArgs
    {
        public Point OldPos { get; set; }
        public double OldWidth { get; set; }
        public double OldHeight { get; set; }
        public ResizeEventArgs(Point oldPos, double oldWidth, double oldHeight) 
            => (OldPos, OldHeight, OldWidth) = (oldPos, oldHeight, oldWidth);
    }
}

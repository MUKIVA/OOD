using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lw9.Model;
using Lw9.Common;
using System.Windows;
using System.Windows.Controls;

namespace Lw9
{
    public class ShapeDataSelector : DataTemplateSelector
    {

        public DataTemplate? Triangle { get; set; }
        public DataTemplate? Rectangle { get; set; }
        public DataTemplate? Ellipse { get; set; }

        public override DataTemplate? SelectTemplate(object item, DependencyObject container)
        {
            ShapeModel shape = (ShapeModel)item;

            if (shape!.ShapeType == ShapeType.Ellipse) return Ellipse;
            if (shape!.ShapeType == ShapeType.Triangle) return Triangle;
            if (shape!.ShapeType == ShapeType.Rectangle) return Rectangle;

            return null;
        }
    }
}

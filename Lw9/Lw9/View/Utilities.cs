using System;
using System.Windows;
using System.Windows.Media;


namespace Lw9.View
{
    public static class Utilities
    {
        public static FrameworkElement? FindAncestor(Type ancestorType, Visual visual)
        {
            while (visual != null && !ancestorType.IsInstanceOfType(visual))
            {
                visual = (Visual)VisualTreeHelper.GetParent(visual);
            }
            return visual as FrameworkElement;
        }

        public static FrameworkElement ConvertToFrameworkElement(Object obj)
        {
            return (FrameworkElement)obj;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using Lw9.Model;
using Lw9.ViewModel;
using System.Windows.Shapes;


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

        public static Type? TryGetType(object obj)
        {
            try
            {
                return obj.GetType();
            }
            catch (Exception)
            {
                return null;
            }
        }

        public static object? TryGetContent(object obj)
        {
            try
            {
                return ((ContentPresenter)obj).Content;
            }
            catch (Exception)
            {
                return null;   
            }
        }
    }
}

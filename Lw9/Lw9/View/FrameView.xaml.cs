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
    /// <summary>
    /// Логика взаимодействия для FrameView.xaml
    /// </summary>
    public partial class FrameView : UserControl
    {
        public FrameView()
        {
            InitializeComponent();
        }

        public static DependencyProperty BindPanelProperty = DependencyProperty.RegisterAttached(
            "BindPanel", typeof(FrameworkElement), typeof(FrameView));

        public FrameworkElement BindPanel
        {
            get => (FrameworkElement)GetValue(BindPanelProperty);
            set => SetValue(BindPanelProperty, value);
        }
    }
}

using System.Windows.Controls;
using System.Windows;

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

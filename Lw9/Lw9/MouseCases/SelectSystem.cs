using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using Lw9.ViewModel;
using Lw9.Model;
using System.Windows.Shapes;

namespace Lw9.DragDrop
{
    public class SelectSystem
    {
        private FrameworkElement? _selectContainer;

        #region IsSelectable

        // Можно ли выделять объект
        public static readonly DependencyProperty IsSelectableProperty = DependencyProperty.RegisterAttached(
            "IsSelectable", typeof(Boolean), typeof(SelectSystem), new PropertyMetadata(false, IsSelectSourceChanged));

        public static Boolean GetIsSelectable(DependencyObject element)
        {
            return (Boolean)element.GetValue(IsSelectableProperty);
        }

        public static void SetIsSelectable(DependencyObject element, Boolean value)
        {
            element.SetValue(IsSelectableProperty, value);
        }

        private static void IsSelectSourceChanged(DependencyObject element, DependencyPropertyChangedEventArgs e)
        {
            var selectSource = element as UIElement;
            if (selectSource == null)
                return;

            //Если IsDraggable = true, объект подписывается на события. Если IsDraggable = false, объект отписывается от событий
            if (Object.Equals(e.NewValue, true))
            {
                selectSource.PreviewMouseRightButtonDown += Instance.MouseRightButtonDown;
            }
            else
            {
                selectSource.PreviewMouseRightButtonDown -= Instance.MouseRightButtonDown;
            }
        }

        #endregion

        #region Select Handlers

        private void MouseRightButtonDown(Object sender, MouseButtonEventArgs e)
        {
            _selectContainer = GetSelectContainer((DependencyObject)sender);
            ISelectField? selectField = _selectContainer.DataContext as ISelectField;

            if (selectField == null) return;

            selectField.SelectObject(Utilities.ConvertToFrameworkElement(sender).DataContext);
        }

        #endregion

        #region SelectContainer

        public static readonly DependencyProperty SelectContainerProperty = DependencyProperty.RegisterAttached(
            "SelectContainer", typeof(FrameworkElement), typeof(SelectSystem), new PropertyMetadata());

        public static FrameworkElement GetSelectContainer(DependencyObject element)
        {
            return (FrameworkElement)element.GetValue(SelectContainerProperty);
        }

        public static void SetSelectContainer(DependencyObject element, FrameworkElement value)
        {
            element.SetValue(SelectContainerProperty, value);
        }

        #endregion

        #region Instance

        private static readonly Lazy<SelectSystem> _Instance = new Lazy<SelectSystem>((() => new SelectSystem()));

        private static SelectSystem Instance
        {
            get => _Instance.Value;
        }

        #endregion

    }
}

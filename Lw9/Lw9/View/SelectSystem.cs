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

namespace Lw9.View
{
    public class SelectSystem
    {
        private ISelectField? _selectContainerContext;

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

            if (Object.Equals(e.NewValue, true))
            {
                selectSource.PreviewMouseLeftButtonDown += Instance.Select;
            }
            else
            {
                selectSource.PreviewMouseLeftButtonDown -= Instance.Select;
            }
        }

        #endregion

        #region Select Handlers

        private void Select(Object sender, MouseButtonEventArgs e)
        {
            //var a = GetSelectContext((DependencyObject)sender);
            //_selectContainer = GetSelectContainer((DependencyObject)sender);
            //ISelectField? selectField = _selectContainer.DataContext as ISelectField;

            //_selectContainer.PreviewMouseLeftButtonDown += Deselect;
            if (_selectContainerContext == null)
                _selectContainerContext = GetSelectContext((DependencyObject)sender);

            if (_selectContainerContext == null) return;

            _selectContainerContext.SelectObject(Utilities.ConvertToFrameworkElement(sender).DataContext);
        }

        #endregion

        #region SelectContext

        public static readonly DependencyProperty SelectContextProperty = DependencyProperty.RegisterAttached(
            "SelectContext", typeof(ISelectField), typeof(SelectSystem), new PropertyMetadata());

        public static ISelectField GetSelectContext(DependencyObject element)
        {
            return (ISelectField)element.GetValue(SelectContextProperty);
        }

        public static void SetSelectContext(DependencyObject element, ISelectField value)
        {
            element.SetValue(SelectContextProperty, value);
        }

        #endregion

        #region IsDeselectField

        public static readonly DependencyProperty IsDeselectFieldProperty = DependencyProperty.RegisterAttached(
            "IsDeselectField", typeof(Boolean), typeof(SelectSystem), new PropertyMetadata(false, OnIsDeselectPropertyChanged));

        public static Boolean GetIsDeselectField(DependencyObject element)
        {
            return (Boolean)element.GetValue(IsDeselectFieldProperty);
        }

        public static void SetIsDeselectField(DependencyObject element, Boolean value)
        {
            element.SetValue(IsDeselectFieldProperty, value);
        }

        private static void OnIsDeselectPropertyChanged(DependencyObject element, DependencyPropertyChangedEventArgs e)
        {
            var deselectSource = element as UIElement;
            if (deselectSource == null)
                return;

            if (Object.Equals(e.NewValue, true))
            {
                deselectSource.PreviewMouseLeftButtonDown += Instance.Deselect;
            }
            else
            {
                deselectSource.PreviewMouseLeftButtonDown -= Instance.Deselect;
            }
        }

        #endregion

        #region Deselect Handlers

        private void Deselect(Object sender, MouseButtonEventArgs e)
        {
            if (_selectContainerContext == null)
                _selectContainerContext = GetSelectContext((DependencyObject)sender);

            _selectContainerContext.ResetSelect();
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

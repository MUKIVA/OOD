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
    public class DragDrop
    {
        private FrameworkElement? _dragContainer;      // Поле относительно которого будут смотреться координаты
        private Boolean _mouseCaptured;                // Проверка захвата
        private Point _initialMousePosition;           // Старые координаты объекта
        private Point _delta;                          // Разница между старыми координатами и новыми
        private Point _oldPosition;
        private ICommand? _dropCommand;                // Команда выполняющаяся после отжатия мыши
        private FrameworkElement? _capturedObject;
        private Window? _window;

        #region DragContainerProperty

        public static readonly DependencyProperty DragContainerProperty = DependencyProperty.RegisterAttached(
            "DragContainer", typeof(FrameworkElement), typeof(DragDrop), new PropertyMetadata());

        public static FrameworkElement GetDragContainer(DependencyObject element)
        {
            return (FrameworkElement)element.GetValue(DragContainerProperty);
        }

        public static void SetDragContainer(DependencyObject element, FrameworkElement value)
        {
            element.SetValue(DragContainerProperty, value);
        }
        
        #endregion

        #region dropCommandProperty

        // Регистрация свойства для получения комманды
        public static readonly DependencyProperty ItemDroppedProperty = DependencyProperty.RegisterAttached(
            "DroppedCommand", typeof(ICommand), typeof(DragDrop), new PropertyMetadata());

        public static ICommand GetDroppedCommand(DependencyObject element)
        {
            return (ICommand)element.GetValue(ItemDroppedProperty);
        }

        public static void SetDroppedCommand(DependencyObject element, ICommand value)
        {
            element.SetValue(ItemDroppedProperty, value);
        }

        #endregion

        #region IsDraggable

        // Можно ли двигать объект
        public static readonly DependencyProperty IsDraggableProperty = DependencyProperty.RegisterAttached(
            "IsDraggable", typeof(Boolean), typeof(DragDrop), new PropertyMetadata(false, IsDragSourceChanged));

        public static Boolean GetIsDraggable(DependencyObject element)
        {
            return (Boolean)element.GetValue(IsDraggableProperty);
        }

        public static void SetIsDraggable(DependencyObject element, Boolean value)
        {
            element.SetValue(IsDraggableProperty, value);
        }

        private static void IsDragSourceChanged(DependencyObject element, DependencyPropertyChangedEventArgs e)
        {
            var dragSource = element as UIElement;
            if (dragSource == null)
                return;

            //Если IsDraggable = true, объект подписывается на события. Если IsDraggable = false, объект отписывается от событий
            if (Object.Equals(e.NewValue, true))
            {
                dragSource.PreviewMouseLeftButtonDown += Instance.CaptureShape;
                dragSource.PreviewMouseLeftButtonUp += Instance.ReleazeShape;
            }
            else
            {
                dragSource.PreviewMouseLeftButtonDown -= Instance.CaptureShape;
                dragSource.PreviewMouseLeftButtonUp -= Instance.ReleazeShape;
            }
        }

        #endregion

        #region Drag handlers

        private void CaptureShape(Object sender, MouseButtonEventArgs e)
        {
            DependencyObject? element = sender as DependencyObject;
            _capturedObject = (FrameworkElement)sender;

            _window = Utilities.FindAncestor(typeof(Window), (Visual)sender) as Window;

            if (element == null) return;

            _dragContainer = GetDragContainer(element);                   // Получаем доступ к области перемещения        
            //ISelectField? selectField = _dragContainer.DataContext as ISelectField;
            //object? selectedObject = selectField?.GetSelectObject();

            //object content = _capturedObject;

            //if (Utilities.TryGetContent(_capturedObject) != null)
            //    content = Utilities.TryGetContent(_capturedObject)!;

            //if (selectedObject != content) return;

            _dropCommand = GetDroppedCommand(element);                 // Получаем пост команду из зависимого объекта
            _initialMousePosition = e.GetPosition(_dragContainer);     // Запоминаем координаты нажатия
            _mouseCaptured = true;                                     // Говорим, что мышка зажата 

           

            _dragContainer!.PreviewMouseMove += MouseMoveHandler;
            _capturedObject.PreviewMouseMove += MouseMoveHandler;
            if (_window != null)
                _window.PreviewMouseLeftButtonUp += ReleazeShape;

            _oldPosition.X = Canvas.GetLeft((UIElement)sender);
            _oldPosition.Y = Canvas.GetTop((UIElement)sender);
            
        }

        private void ReleazeShape(Object sender, MouseButtonEventArgs e)
        {
            FinalizeEvent(sender, e);
        }

        private void FinalizeEvent(Object sender, MouseEventArgs e)
        {
            _mouseCaptured = false;                                     // Говорим, что мышка отжата
            _capturedObject!.PreviewMouseMove -= MouseMoveHandler;
            _dragContainer!.PreviewMouseMove -= MouseMoveHandler;
            if (_window != null)
                _window.PreviewMouseLeftButtonUp -= ReleazeShape;
            if (_dropCommand != null && _dropCommand.CanExecute(null))  // Исполняем пост команду
                _dropCommand.Execute(null);
        }

        private void MouseMoveHandler(Object sender, MouseEventArgs e)
        {
            if (!_mouseCaptured) return;                                // Нельзя перемещать объект, когда мышка не зажата

            var currentPoint = e.GetPosition(_dragContainer);           // Получаем координаты мышки относительно контейнера

            _delta.X = currentPoint.X - _initialMousePosition.X;        // Рассчитываем разность между новыми и старыми координатами
            _delta.Y = currentPoint.Y - _initialMousePosition.Y;

            // Перемещаем объект
            Canvas.SetLeft(_capturedObject, _oldPosition.X + _delta.X);
            Canvas.SetTop(_capturedObject, _oldPosition.Y + _delta.Y);
        }

        #endregion

        #region Instance

        private static readonly Lazy<DragDrop> _Instance = new Lazy<DragDrop>((() => new DragDrop()));

        private static DragDrop Instance
        {
            get => _Instance.Value;
        }

        #endregion

    }
}

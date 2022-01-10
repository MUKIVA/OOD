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

namespace Lw9.DragDrop
{
    public class ResizeControl
    {
        private const double MIN_SIZE = 50;

        private FrameworkElement? _dragContainer;
        private Boolean _mouseCaptured;
        private Point _initialMousePosition;
        private Point _delta;
        private Point _oldPosition;
        private Point _oldSize;
        private DependencyObject? _sourceObject;
        private FrameworkElement? _frameContainer;
        private FrameworkElement? _bottomRightMarker;
        private FrameworkElement? _bottomLeftMarker;
        private FrameworkElement? _topLeftMarker;
        private FrameworkElement? _topRightMarker;


        #region IsResizeFrame

        public static readonly DependencyProperty IsResizeFrameProperty = DependencyProperty.RegisterAttached(
            "IsResizeFrame", typeof(Boolean), typeof(ResizeControl), new PropertyMetadata(false, IsResizeSourceChanged));

        public static Boolean GetIsResizeFrame(DependencyObject element)
        {
            return (Boolean)element.GetValue(IsResizeFrameProperty);
        }

        public static void SetIsResizeFrame(DependencyObject element, Boolean value)
        {
            element.SetValue(IsResizeFrameProperty, value);
        }

        private static void IsResizeSourceChanged(DependencyObject element, DependencyPropertyChangedEventArgs e)
        {
            var resizeSource = element as UIElement;
            if (resizeSource == null)
                return;

            if (Object.Equals(e.NewValue, true))
            {
                resizeSource.IsVisibleChanged += Instance.Initialize;
                Instance._sourceObject = resizeSource;   
            }
        }

        private void RegistrationEvents(FrameworkElement el)
        {
            if (el != null)
            {
                el.PreviewMouseLeftButtonDown += CaptureMarker;
                el.PreviewMouseLeftButtonUp += ReleaseMarker; 
            }
        }

        private void Initialize(object sender, DependencyPropertyChangedEventArgs e)
        {

            Instance._bottomLeftMarker = GetBottomLeftMarker((DependencyObject)sender );
            Instance._bottomRightMarker = GetBottomRightMarker((DependencyObject)sender);
            Instance._topLeftMarker = GetTopLeftMarker((DependencyObject)sender);
            Instance._topRightMarker = GetTopRightMarker((DependencyObject)sender);

            RegistrationEvents(Instance._bottomRightMarker);
            RegistrationEvents(Instance._bottomLeftMarker);
            RegistrationEvents(Instance._topLeftMarker);
            RegistrationEvents(Instance._topRightMarker);
            

        }

        #endregion

        #region ResizeHandlers

        private void ReleaseMarker(Object sender, MouseButtonEventArgs e)
        {
            _mouseCaptured = false;

            if (_dragContainer == null) return;

            _dragContainer!.PreviewMouseMove -= BottomRightHandler;
            _dragContainer.PreviewMouseMove -= BottomLeftHandler;
            _dragContainer.PreviewMouseMove -= TopLeftHandler;
            _dragContainer.PreviewMouseMove -= TopRightHandler;
            _bottomRightMarker!.PreviewMouseMove -= BottomRightHandler;
            _bottomLeftMarker!.PreviewMouseMove -= BottomLeftHandler;
            _topLeftMarker!.PreviewMouseMove -= TopLeftHandler;
            _topRightMarker!.PreviewMouseMove -= TopRightHandler;

            _dragContainer.PreviewMouseLeftButtonUp -= ReleaseMarker;
        }

        private void CaptureMarker(Object sender, MouseButtonEventArgs e)
        {
            DependencyObject? element = sender as DependencyObject;

            if (element == null) return;

            _frameContainer = GetFrameContainer(_sourceObject!);                // Получаем контейнер фрейма
            _dragContainer = GetDragContainer(_sourceObject!);                // Получаем доступ к области перемещения
            _initialMousePosition = e.GetPosition(_dragContainer);              // Запоминаем координаты нажатия

            _oldPosition.X = Canvas.GetLeft(_frameContainer);                   // Получаем старые значения координат
            _oldPosition.Y = Canvas.GetTop(_frameContainer);
            _oldSize.X     = _frameContainer.Width;                             // Получачем старые значения размеров
            _oldSize.Y     = _frameContainer.Height; 

            if (_dragContainer == null) return;

            // В зависимости от нажатого маркера задаем обработчик изменения размера
            if (sender == _bottomRightMarker)
            {
                _dragContainer.PreviewMouseMove += BottomRightHandler;
                _bottomRightMarker.PreviewMouseMove += BottomRightHandler;
            }

            if (sender == _bottomLeftMarker)
            { 
                _dragContainer.PreviewMouseMove += BottomLeftHandler;
                _bottomLeftMarker.PreviewMouseMove += BottomLeftHandler;
            }
            if (sender == _topLeftMarker)
            {
                _dragContainer.PreviewMouseMove += TopLeftHandler;
                _topLeftMarker.PreviewMouseMove += TopLeftHandler;
            }
            if (sender == _topRightMarker)
            { 
                _dragContainer.PreviewMouseMove += TopRightHandler;
                _topRightMarker.PreviewMouseMove += TopRightHandler;
            }

            _dragContainer.PreviewMouseLeftButtonUp += ReleaseMarker;

            _mouseCaptured = true;

            //_dropCommand = GetDroppedCommand(element);                        // Получаем пост команду из зависимого объекта

        }


        private bool ValidateSize(double size) => size > MIN_SIZE;
        
        private void TopLeftHandler(Object sender, MouseEventArgs e)
        {
            if (!_mouseCaptured) return;

            var currentPoint = e.GetPosition(_dragContainer);
            _delta.X = currentPoint.X - _initialMousePosition.X;
            _delta.Y = currentPoint.Y - _initialMousePosition.Y;

            // Меняем размеры на дельту от старых значений

            _frameContainer!.Height = (ValidateSize(_oldSize.Y - _delta.Y)) ? _oldSize.Y - _delta.Y : MIN_SIZE;
            _frameContainer!.Width = (ValidateSize(_oldSize.X - _delta.X)) ? _oldSize.X - _delta.X : MIN_SIZE;
            if (ValidateSize(_oldSize.Y - _delta.Y)) 
                Canvas.SetTop(_frameContainer, _oldPosition.Y + _delta.Y);
            if (ValidateSize(_oldSize.X - _delta.X))
                Canvas.SetLeft(_frameContainer, _oldPosition.X + _delta.X);
        }

        private void TopRightHandler(Object sender, MouseEventArgs e)
        {
            if (!_mouseCaptured) return;

            var currentPoint = e.GetPosition(_dragContainer);
            _delta.X = currentPoint.X - _initialMousePosition.X;
            _delta.Y = currentPoint.Y - _initialMousePosition.Y;
            // Изменяем значения на дельту от старых

            _frameContainer!.Height = ValidateSize(_oldSize.Y - _delta.Y) ? _oldSize.Y - _delta.Y : MIN_SIZE;
            _frameContainer!.Width = ValidateSize(_oldSize.X + _delta.X) ? _oldSize.X + _delta.X : MIN_SIZE;

            if (ValidateSize(_oldSize.Y - _delta.Y))
                Canvas.SetTop(_frameContainer, _oldPosition.Y + _delta.Y);

        }

        private void BottomLeftHandler(Object sender, MouseEventArgs e)
        {
            if (!_mouseCaptured) return;

            var currentPoint = e.GetPosition(_dragContainer);
            _delta.X = currentPoint.X - _initialMousePosition.X;
            _delta.Y = currentPoint.Y - _initialMousePosition.Y;

            double a = _oldPosition.X + _delta.X;

            // Изменяем значения на дельту от старых

            _frameContainer!.Height = ValidateSize(_oldSize.Y + _delta.Y) ? _oldSize.Y + _delta.Y : MIN_SIZE;
            _frameContainer!.Width  = ValidateSize(_oldSize.X - _delta.X) ? _oldSize.X - _delta.X : MIN_SIZE;
            if(ValidateSize(_oldSize.X - _delta.X))
                Canvas.SetLeft(_frameContainer, a);
        }

        private void BottomRightHandler(Object sender, MouseEventArgs e)
        {
            if (!_mouseCaptured) return;

            var currentPoint = e.GetPosition(_dragContainer);
            _delta.X = currentPoint.X - _initialMousePosition.X;
            _delta.Y = currentPoint.Y - _initialMousePosition.Y;

            // Изменяем значения на дельту от старых

            _frameContainer!.Height = ValidateSize(_oldSize.Y + _delta.Y) ? _oldSize.Y + _delta.Y : MIN_SIZE;
            _frameContainer!.Width = ValidateSize(_oldSize.X + _delta.X) ? _oldSize.X + _delta.X : MIN_SIZE;

        }

        #endregion

        #region DragContainerProperty

        public static readonly DependencyProperty DragContainerProperty = DependencyProperty.RegisterAttached(
            "DragContainer", typeof(FrameworkElement), typeof(ResizeControl), new PropertyMetadata());

        public static FrameworkElement GetDragContainer(DependencyObject element)
        {
            return (FrameworkElement)element.GetValue(DragContainerProperty);
        }

        public static void SetDragContainer(DependencyObject element, FrameworkElement value)
        {
            element.SetValue(DragContainerProperty, value);
        }

        #endregion

        #region FrameContainerProperty

        public static readonly DependencyProperty FrameContainerProperty = DependencyProperty.RegisterAttached(
            "FrameContainer", typeof(FrameworkElement), typeof(ResizeControl), new PropertyMetadata());

        public static FrameworkElement GetFrameContainer(DependencyObject element)
        {
            return (FrameworkElement)element.GetValue(FrameContainerProperty);
        }

        public static void SetFrameContainer(DependencyObject element, Canvas value)
        {
            element.SetValue(FrameContainerProperty, value);
        }

        #endregion

        #region BottomRightMarkerProperty

        public static readonly DependencyProperty BottomRightMarkerProperty = DependencyProperty.RegisterAttached(
            "BottomRightMarker", typeof(FrameworkElement), typeof(ResizeControl), new PropertyMetadata());

        public static FrameworkElement GetBottomRightMarker(DependencyObject element)
        {
            return (FrameworkElement)element.GetValue(BottomRightMarkerProperty);
        }

        public static void SetBottomRightMarker(DependencyObject element, FrameworkElement value)
        {
            element.SetValue(BottomRightMarkerProperty, value);
        }

        #endregion

        #region BottomLeftMarkerProperty

        public static readonly DependencyProperty BottomLeftMarkerProperty = DependencyProperty.RegisterAttached(
            "BottomLeftMarker", typeof(FrameworkElement), typeof(ResizeControl), new PropertyMetadata());

        public static FrameworkElement GetBottomLeftMarker(DependencyObject element)
        {
            return (FrameworkElement)element.GetValue(BottomLeftMarkerProperty);
        }

        public static void SetBottomLeftMarker(DependencyObject element, FrameworkElement value)
        {
            element.SetValue(BottomLeftMarkerProperty, value);
        }

        #endregion

        #region TopLeftMarkerProperty

        public static readonly DependencyProperty TopLeftMarkerProperty = DependencyProperty.RegisterAttached(
            "TopLeftMarker", typeof(FrameworkElement), typeof(ResizeControl), new PropertyMetadata());

        public static FrameworkElement GetTopLeftMarker(DependencyObject element)
        {
            return (FrameworkElement)element.GetValue(TopLeftMarkerProperty);
        }

        public static void SetTopLeftMarker(DependencyObject element, FrameworkElement value)
        {
            element.SetValue(TopLeftMarkerProperty, value);
        }

        #endregion

        #region TopRightMarkerProperty

        public static readonly DependencyProperty TopRightMarkerProperty = DependencyProperty.RegisterAttached(
            "TopRightMarker", typeof(FrameworkElement), typeof(ResizeControl), new PropertyMetadata());

        public static FrameworkElement GetTopRightMarker(DependencyObject element)
        {
            return (FrameworkElement)element.GetValue(TopRightMarkerProperty);
        }

        public static void SetTopRightMarker(DependencyObject element, FrameworkElement value)
        {
            element.SetValue(TopRightMarkerProperty, value);
        }

        #endregion

        #region Instance

        private static readonly Lazy<ResizeControl> _Instance = new Lazy<ResizeControl>((() => new ResizeControl()));

        private static ResizeControl Instance
        {
            get => _Instance.Value;
        }

        #endregion
    }
}

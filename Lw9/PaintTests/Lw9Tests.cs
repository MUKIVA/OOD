using System;
using Xunit;
using Lw9.ViewModel;
using Lw9.Model;
using Lw9.Common;
using Lw9.HistoryService;
using System.Collections.Specialized;
using System.Windows.Media.Imaging;
using System.Windows.Media;
using System.Windows;

namespace PaintTests
{

    public static class Validate
    {
        public static bool SubscribePropertyChange(string requirePropertyName, string factPropertyName)
        {
            return requirePropertyName == factPropertyName;
        }

        public static bool SubscribeCollectionChange(NotifyCollectionChangedAction requireAction, NotifyCollectionChangedAction factAction)
        {
            return requireAction == factAction;
        }

        public static bool BitMapEqual(BitmapSource requireMap, BitmapSource factMap)
        {
            return (requireMap.DpiX == factMap.DpiX
                && requireMap.DpiY == factMap.DpiY
                && requireMap.PixelHeight == factMap.PixelHeight
                && requireMap.PixelWidth == factMap.PixelWidth
                && requireMap.Format == factMap.Format
                && requireMap.Palette == factMap.Palette);
        }
        public static bool ShapeEqual(ShapeModel require, ShapeModel fact)
        {
            return (require.CanvasLeft == fact.CanvasLeft
                && require.CanvasTop == fact.CanvasTop
                && require.Height == fact.Height
                && require.Width == fact.Width);
        }
    }

    public class ShapeModelTest
    {

        private readonly ShapeModel _shape;

        public ShapeModelTest()
        {
            _shape = new ShapeModel
                (
                    ShapeType.Ellipse,
                    DefaultShapeConfig.WIDTH,
                    DefaultShapeConfig.HEIGHT,
                    DefaultShapeConfig.LEFT,
                    DefaultShapeConfig.TOP
                );
        }

        [Fact]
        public void ShapeTypeChange()
        {
            ShapeType require = ShapeType.Rectangle;
            _shape.ShapeType = require;
            Assert.Equal(require, _shape.ShapeType);       
        }

        [Theory]
        [InlineData(300)]
        [InlineData(0)]
        [InlineData(-100)]
        public void ShapeWidthChange(double require)
        {
            _shape.Width = require;
            Assert.Equal(require, _shape.Width);
        }

        [Theory]
        [InlineData(300)]
        [InlineData(0)]
        [InlineData(-100)]
        public void ShapeHeightChange(double require)
        {
            _shape.Height = require;
            Assert.Equal(require, _shape.Height);
        }

        [Theory]
        [InlineData(300)]
        [InlineData(0)]
        [InlineData(-100)]
        public void ShapeCanvasTopChange(double require)
        {
            _shape.CanvasTop = require;
            Assert.Equal(require, _shape.CanvasTop);
        }

        [Theory]
        [InlineData(300)]
        [InlineData(0)]
        [InlineData(-100)]
        public void ShapeCanvasLeftChange(double require)
        {
            _shape.CanvasLeft = require;
            Assert.Equal(require, _shape.CanvasLeft);
        }

        [Fact]
        public void SubscribeHeightChange()
        {
            bool result = false;
            _shape.PropertyChanged += (s, e) => result = Validate.SubscribePropertyChange("Height", e.PropertyName);
            _shape.Height = _shape.Height + 10;
            Assert.True(result);
        }

        [Fact]
        public void SubscribeWidthChange()
        {
            bool result = false;
            _shape.PropertyChanged += (s, e) => result = Validate.SubscribePropertyChange("Width", e.PropertyName);
            _shape.Width = _shape.Width + 10;
            Assert.True(result);
        }

        [Fact]
        public void SubscribeCanvasTopChange()
        {
            bool result = false;
            _shape.PropertyChanged += (s, e) => result = Validate.SubscribePropertyChange("CanvasTop", e.PropertyName);
            _shape.CanvasTop = _shape.CanvasTop + 10;
            Assert.True(result);
        }

        [Fact]
        public void SubscribeCanvasLeftChange()
        {
            bool result = false;
            _shape.PropertyChanged += (s, e) => result = Validate.SubscribePropertyChange("CanvasLeft", e.PropertyName);
            _shape.CanvasLeft = _shape.CanvasLeft+ 10;
            Assert.True(result);
        }
    }

    public class CanvasModelTests
    {
        private CanvasModel _canvas;
        private readonly ShapeModel _shape = new ShapeModel
                (
                    ShapeType.Ellipse,
                    DefaultShapeConfig.WIDTH,
                    DefaultShapeConfig.HEIGHT,
                    DefaultShapeConfig.LEFT,
                    DefaultShapeConfig.TOP
                );

        public CanvasModelTests()
        {
            _canvas = new CanvasModel();
        }

        [Theory]
        [InlineData(300)]
        [InlineData(0)]
        [InlineData(-100)]
        public void CanvasModelWidthChange(int require)
        {
            _canvas.Width = require;
            Assert.Equal(require, _canvas.Width);
        }

        [Theory]
        [InlineData(300)]
        [InlineData(0)]
        [InlineData(-100)]
        public void CanvasModelHeightChange(int require)
        {
            _canvas.Width = require;
            Assert.Equal(require, _canvas.Width);
        }

        [Theory]
        [InlineData("")]
        [InlineData(@"\img\test.jpg")]
        [InlineData(null)]
        public void CanvasModelImagePathChange(string require)
        {
            _canvas.PicturePath = require;
            Assert.Equal(require, _canvas.PicturePath);
        }

        [Fact]
        public void CanvasAddShape()
        {
            _canvas.Shapes.Add(new ShapeModel());
            int shapesCount = _canvas.Shapes.Count;
            int require = 1;
            Assert.Equal(require, shapesCount);
        }

        [Fact]
        public void CanvasRemoveShape()
        {
            var shape = new ShapeModel();
            _canvas.Shapes.Add(shape);
            _canvas.Shapes.Remove(shape);
            int shapesCount = _canvas.Shapes.Count;
            int require = 0;
            Assert.Equal(require, shapesCount);
        }

        [Fact]
        public void SubscribeWidthChange()
        {
            bool result = false;
            _canvas.PropertyChanged += (s, e) => result = Validate.SubscribePropertyChange("Width", e.PropertyName);
            _canvas.Width = _canvas.Width + 10;
            Assert.True(result);
        }

        [Fact]
        public void SubscribePicturePathChange()
        {
            bool result = false;
            _canvas.PropertyChanged += (s, e) => result = Validate.SubscribePropertyChange("PicturePath", e.PropertyName);
            _canvas.PicturePath = _canvas.PicturePath + 10;
            Assert.True(result);
        }

        [Fact]
        public void SubscribeHeightChange()
        {
            bool result = false;
            _canvas.PropertyChanged += (s, e) => result = Validate.SubscribePropertyChange("Height", e.PropertyName);
            _canvas.Height = _canvas.Height + 10;
            Assert.True(result);
        }

        [Fact]
        public void SubscribeShapeCollectionChangeAdd()
        {
            bool result = false;
            _canvas.Shapes.CollectionChanged += (s, e) 
                => result = Validate.SubscribeCollectionChange(NotifyCollectionChangedAction.Add, e.Action);
            _canvas.Shapes.Add(_shape);
            Assert.True(result);
        }

        [Fact]
        public void SubscribeShapeCollectionChangeRemove()
        {
            bool result = false;
            _canvas.Shapes.Add(_shape);
            _canvas.Shapes.CollectionChanged += (s, e)
                => result = Validate.SubscribeCollectionChange(NotifyCollectionChangedAction.Remove, e.Action);
            _canvas.Shapes.Remove(_shape);
            Assert.True(result);
        }

        [Fact]
        public void SubscribeShapeCollectionChangeReset()
        {
            bool result = false;
            _canvas.Shapes.Add(_shape);
            _canvas.Shapes.CollectionChanged += (s, e)
                => result = Validate.SubscribeCollectionChange(NotifyCollectionChangedAction.Reset, e.Action);
            _canvas.Shapes.Clear();
            Assert.True(result);
        }
    }

    public class ShapeViewModelTests
    {
        private ShapeViewModel _shapeVM;
        private readonly ShapeModel _shape;

        public ShapeViewModelTests()
        {
            _shape = new ShapeModel
                (
                    ShapeType.Ellipse,
                    DefaultShapeConfig.WIDTH,
                    DefaultShapeConfig.HEIGHT,
                    DefaultShapeConfig.LEFT,
                    DefaultShapeConfig.TOP
                );
            _shapeVM = new ShapeViewModel(_shape);
        }

        [Theory]
        [InlineData(150)]
        [InlineData(0)]
        [InlineData(-150)]
        public void UpdateModelWidth(double require)
        {
            _shapeVM.Width = require;
            Assert.Equal(require, _shape.Width);
        }

        [Theory]
        [InlineData(150)]
        [InlineData(0)]
        [InlineData(-150)]
        public void UpdateModelHeight(double require)
        {
            _shapeVM.Height = require;
            Assert.Equal(require, _shape.Height);
        }

        [Theory]
        [InlineData(150)]
        [InlineData(0)]
        [InlineData(-150)]
        public void UpdateModelCanvasTop(double require)
        {
            _shapeVM.CanvasTop = require;
            Assert.Equal(require, _shape.CanvasTop);
        }

        [Theory]
        [InlineData(150)]
        [InlineData(0)]
        [InlineData(-150)]
        public void UpdateModelCanvasLeft(double require)
        {
            _shapeVM.CanvasLeft = require;
            Assert.Equal(require, _shape.CanvasLeft);
        }

        [Fact]
        public void SubscribeHeightChange()
        {
            bool result = false;
            _shapeVM.PropertyChanged += (s, e) => result = Validate.SubscribePropertyChange("Height", e.PropertyName);
            _shapeVM.Height = _shapeVM.Height + 10;
            Assert.True(result);
        }

        [Fact]
        public void SubscribeWidthChange()
        {
            bool result = false;
            _shapeVM.PropertyChanged += (s, e) => result = Validate.SubscribePropertyChange("Width", e.PropertyName);
            _shapeVM.Width = _shapeVM.Width + 10;
            Assert.True(result);
        }

        [Fact]
        public void SubscribeCanvasTopChange()
        {
            bool result = false;
            _shapeVM.PropertyChanged += (s, e) => result = Validate.SubscribePropertyChange("CanvasTop", e.PropertyName);
            _shapeVM.CanvasTop = _shapeVM.CanvasTop + 10;
            Assert.True(result);
        }

        [Fact]
        public void SubscribeCanvasLeftChange()
        {
            bool result = false;
            _shapeVM.PropertyChanged += (s, e) => result = Validate.SubscribePropertyChange("CanvasLeft", e.PropertyName);
            _shapeVM.CanvasLeft = _shapeVM.CanvasLeft + 10;
            Assert.True(result);
        }

    }

    public class SelectedShapeViewModelTests
    {
        private SelectedShapeViewModel _selectedShapeVM;
        private ShapeViewModel _shapeVM;
        private ShapeModel _shape = new ShapeModel
                (
                    ShapeType.Ellipse,
                    DefaultShapeConfig.WIDTH,
                    DefaultShapeConfig.HEIGHT,
                    DefaultShapeConfig.LEFT,
                    DefaultShapeConfig.TOP
                );

        public SelectedShapeViewModelTests()
        {
            _selectedShapeVM = new SelectedShapeViewModel();
            _shapeVM = new ShapeViewModel(_shape);
        }

        [Fact]
        public void SelectedShapeChange()
        {
            _selectedShapeVM.SelectedShape = _shapeVM;
            Assert.Equal(_shapeVM, _selectedShapeVM.SelectedShape);
        }

        [Fact]
        public void SelectedShapeChangeNull()
        {
            _selectedShapeVM.SelectedShape = null;
            Assert.Null(_selectedShapeVM.SelectedShape);
        }
    }

    public class CanvasViewModelTests
    {
        private CanvasModel _canvas = new();
        private CanvasViewModel _canvasVM;
        private SelectedShapeViewModel _selectedShapeVM = new();
        private ShapeViewModel _shapeVM;
        private readonly ShapeModel _shape;

        public CanvasViewModelTests()
        {
            _shape = new ShapeModel
                (
                    ShapeType.Ellipse,
                    DefaultShapeConfig.WIDTH,
                    DefaultShapeConfig.HEIGHT,
                    DefaultShapeConfig.LEFT,
                    DefaultShapeConfig.TOP
                );
            _shapeVM = new ShapeViewModel(_shape);
            _canvasVM = new CanvasViewModel(_canvas, _selectedShapeVM);
        }

        [Fact]
        public void AddEllipse()
        {
            _canvasVM.AddEllipse.Execute(null);
            Assert.True(_canvasVM.Shapes.Count == _canvas.Shapes.Count);
        }

        [Fact]
        public void AddRectangle()
        {
            _canvasVM.AddRectangle.Execute(null);
            Assert.True(_canvasVM.Shapes.Count == _canvas.Shapes.Count);
        }

        [Fact]
        public void AddTriangle()
        {
            _canvasVM.AddTriangle.Execute(null);
            Assert.True(_canvasVM.Shapes.Count == _canvas.Shapes.Count);
        }

        [Fact]
        public void DeleteShape()
        {
            _canvasVM.AddTriangle.Execute(null);
            _selectedShapeVM.SelectedShape = _canvasVM.Shapes[0];
            _canvasVM.DeleteShape.Execute(null);

            Assert.True(_canvasVM.Shapes.Count == _canvas.Shapes.Count);
        }

        [Fact]
        public void SelectShapeTest()
        {
            _canvasVM.AddTriangle.Execute(null);
            _canvasVM.SelectShape.Execute(_canvasVM.Shapes[0]);

            Assert.Equal(_canvasVM.Shapes[0], _selectedShapeVM.SelectedShape);
        }

        [Fact]
        public void ResetSelectTest()
        {
            _canvasVM.AddTriangle.Execute(null);
            _canvasVM.SelectShape.Execute(_canvasVM.Shapes[0]);
            _canvasVM.ResetSelectionShape.Execute(null);

            Assert.Null(_selectedShapeVM.SelectedShape);
        }

        [Theory]
        [InlineData(150)]
        [InlineData(0)]
        [InlineData(-150)]
        public void UpdateHeight(int require)
        {
            _canvasVM.Height = require;
            Assert.Equal(require, _canvas.Height);
        }

        [Theory]
        [InlineData(150)]
        [InlineData(0)]
        [InlineData(-150)]
        public void UpdateWidth(int require)
        {
            _canvasVM.Width = require;
            Assert.Equal(require, _canvas.Width);
        }

        [Fact]
        public void SelectObjectTest()
        {
            _canvasVM.AddTriangle.Execute(null);
            _canvasVM.SelectObject(_canvasVM.Shapes[0]);
            Assert.Equal(_canvasVM.Shapes[0], _selectedShapeVM.SelectedShape);
        }

        [Fact]
        public void GetSelectObjectTest()
        {
            _canvasVM.AddEllipse.Execute(null);
            _canvasVM.SelectObject(_canvasVM.Shapes[0]);
            object select = _canvasVM.GetSelectObject();
            Assert.Equal(select, _canvasVM.Shapes[0]);
        }

        [Fact]
        public void ResetObjectTest()
        {
            _canvasVM.AddTriangle.Execute(null);
            _canvasVM.SelectObject(_canvasVM.Shapes[0]);
            _canvasVM.ResetSelect();
            Assert.Null(_selectedShapeVM.SelectedShape);
        }

        [Fact]
        public void GetEmptyBitmap()
        {
            var bitmap = _canvasVM.ImageSource;
            var empty = BitmapImage.Create(1, 1, 1, 1, PixelFormats.BlackWhite, null, new byte[] { 255 }, 1);
            Assert.True(Validate.BitMapEqual(empty, bitmap));
        }

        [Fact]
        public void GetFilledBitmap()
        {
            _canvas.PicturePath = @"\..\..\..\testImg\test.jpg";
            var image = new BitmapImage();
            image.BeginInit();
            image.UriSource = new Uri(Environment.CurrentDirectory + _canvas.PicturePath);
            image.EndInit();

            byte[] pixels = new byte[image.PixelHeight * image.PixelWidth * 4];
            image.CopyPixels(pixels, image.PixelWidth * 4, 0);
            var filled = BitmapImage.Create(
                image.PixelWidth,
                image.PixelHeight,
                image.DpiX,
                image.DpiY,
                image.Format,
                image.Palette,
                pixels, image.PixelWidth * 4);
            var bitmap = _canvasVM.ImageSource;
            Assert.True(Validate.BitMapEqual(filled, bitmap));
        }
    }

    public class MockUnduableCommand : IUnduableCommand
    {
        public void Execute()
        {
        }

        public void Unexecute()
        {
        }
    }

    public class HistoryTests
    {
        private History _history;

        public HistoryTests()
        {
            _history = new History();
        }

        [Fact]
        public void AddCommandTest()
        {
            _history.AddToHistory(new MockUnduableCommand());
            Assert.True(_history.CanUndo());
        }

        [Fact]
        public void UndoTest()
        {
            _history.AddToHistory(new MockUnduableCommand());
            _history.UndoCommand.Execute(null);
            Assert.True(_history.CanRedo());
        }

        [Fact]
        public void RedoTest()
        {
            _history.AddToHistory(new MockUnduableCommand());
            _history.UndoCommand.Execute(null);
            _history.RedoCommand.Execute(null);
            Assert.True(_history.CanUndo());
        }
    }

    public class ShapeListViewModelTests
    {
        private ShapeListViewModel _shapeListVM;
        private CanvasModel _canvas = new();
        private SelectedShapeViewModel _selectedShapeVM;
        private ShapeModel _shape = new ShapeModel
                (
                    ShapeType.Ellipse,
                    DefaultShapeConfig.WIDTH,
                    DefaultShapeConfig.HEIGHT,
                    DefaultShapeConfig.LEFT,
                    DefaultShapeConfig.TOP
                );
        private ShapeViewModel _shapeVM;

        public ShapeListViewModelTests()
        {
            _shapeVM = new(_shape);
            _selectedShapeVM = new SelectedShapeViewModel();
            _shapeListVM = new ShapeListViewModel(_canvas, _selectedShapeVM);
        }

        [Fact]
        public void SelectedShapeChange()
        {
            _selectedShapeVM.SelectedShape = _shapeVM;
            Assert.Equal(_shapeVM, _shapeListVM.SelectedShapeVM.SelectedShape);
        }

        [Fact]
        public void AddEllipse()
        {
            _shape.ShapeType = ShapeType.Ellipse;
            _canvas.Shapes.Add(_shape);
            Assert.True(_shapeListVM.Shapes.Count == _canvas.Shapes.Count);
        }

        [Fact]
        public void AddRectangle()
        {
            _shape.ShapeType = ShapeType.Rectangle;
            _canvas.Shapes.Add(_shape);
            Assert.True(_shapeListVM.Shapes.Count == _canvas.Shapes.Count);
        }

        [Fact]
        public void AddTriangle()
        {
            _shape.ShapeType = ShapeType.Triangle;
            _canvas.Shapes.Add(_shape);
            Assert.True(_shapeListVM.Shapes.Count == _canvas.Shapes.Count);
        }

        [Fact]
        public void DeleteShape()
        {
            _shape.ShapeType = ShapeType.Triangle;
            _canvas.Shapes.Add(_shape);
            _canvas.Shapes.RemoveAt(0);

            Assert.True(_shapeListVM.Shapes.Count == _canvas.Shapes.Count);
        }
    }

    public class UndoableCommandTests
    {
        private ShapeListViewModel _shapeListVM;
        private CanvasModel _canvas = new();
        private SelectedShapeViewModel _selectedShapeVM;
        private ShapeViewModel _shapeVM;
        private ShapeModel _shape = new ShapeModel
                (
                    ShapeType.Ellipse,
                    DefaultShapeConfig.WIDTH,
                    DefaultShapeConfig.HEIGHT,
                    DefaultShapeConfig.LEFT,
                    DefaultShapeConfig.TOP
                );

        public UndoableCommandTests()
        {
            _selectedShapeVM = new SelectedShapeViewModel();
            _shapeVM = new ShapeViewModel(_shape);
            _shapeListVM = new ShapeListViewModel(_canvas, _selectedShapeVM);
        }

        [Fact]
        public void ChangeBackgroundCommandExecute()
        {
            string require = @"\..\..\..\testImg\test.jpg";
            ChangeBackgroundCommand command = new(_canvas, require, false);
            command.Execute();
            Assert.Equal(require, _canvas.PicturePath);
        }

        [Fact]
        public void ChangeBackgroundCommandUnexecute()
        {
            string require = _canvas.PicturePath;
            ChangeBackgroundCommand command = new(_canvas, @"\..\..\..\testImg\test.jpg", false);
            command.Execute();
            command.Unexecute();
            Assert.Equal(require, _canvas.PicturePath);
        }

        [Fact]
        public void ChangeFrameCommandExecute()
        {
            ShapeModel require = new ShapeModel(ShapeType.Ellipse, 100, 100, 270, 190);
            ChangeFrameCommand command = new(_shapeVM, new Point(150, 150), 200, 200);
            command.Execute();
            Assert.True(Validate.ShapeEqual(require, _shape));
        }

        [Fact]
        public void ChangeFrameCommandUnexecute()
        {
            ShapeModel require = new ShapeModel(ShapeType.Ellipse, 200, 200, 150, 150);
            ChangeFrameCommand command = new(_shapeVM, new Point(150, 150), 200, 200);
            command.Execute();
            command.Unexecute();
            Assert.True(Validate.ShapeEqual(require, _shape));
        }

        [Fact]
        public void CreateShapeCommandExecute()
        {
            CreateShapeCommand command = new CreateShapeCommand(_canvas, _shape, _selectedShapeVM);
            command.Execute();
            Assert.True(_canvas.Shapes.Count > 0);
        }

        [Fact]
        public void CreateShapeCommandUnexecute()
        {
            CreateShapeCommand command = new CreateShapeCommand(_canvas, _shape, _selectedShapeVM);
            command.Execute();
            command.Unexecute();
            Assert.True(_canvas.Shapes.Count == 0);
        }

        [Fact]
        public void DeleteShapeCommandExecute()
        {
            _canvas.Shapes.Add(_shape);
            DeleteShapeCommand command = new DeleteShapeCommand(_canvas, 0);
            command.Execute();
            Assert.True(_canvas.Shapes.Count == 0);
        }

        [Fact]
        public void DeleteShapeCommandUnexecute()
        {
            _canvas.Shapes.Add(_shape);
            DeleteShapeCommand command = new DeleteShapeCommand(_canvas, 0);
            command.Execute();
            command.Unexecute();
            Assert.True(_canvas.Shapes.Count > 0);
        }
    }
}

using System;
using Xunit;
using Lw9.ViewModel;
using Lw9.Model;
using Lw9.Common;

namespace PaintTests
{
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
    }

    public class CanvasModelTests
    {
        private CanvasModel _canvas;

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

        //[Fact]
        //public void CanvasAddShape()
        //{
        //    _canvas.Shapes.Add(new ShapeModel());
        //    int shapesCount = _canvas.Shapes.Count;
        //    int require = 1;
        //    Assert.Equal(require, shapesCount);   
        //}

        //[Fact]
        //public void CanvasRemoveShape()
        //{
        //    var shape = new ShapeModel();
        //    _canvas.Shapes.Add(shape);
        //    _canvas.Shapes.Remove(shape);
        //    int shapesCount = _canvas.Shapes.Count;
        //    int require = 0;
        //    Assert.Equal(require, shapesCount);
        //}
    }
}

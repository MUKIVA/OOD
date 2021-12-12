using Xunit;
using Document;
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

namespace Lw5Sharp_tests
{

    static class Validator
    {
        static public bool ValidateParagraph(IDocument document, int position, string text)
        {
            CDocumentItem item = document.GetItem(position);
            IParagraph? paragraph = item.Paragraph;
            if (paragraph == null)
                return false;
            if (paragraph.Text != text)
                return false;
            return true;
        }

        static public bool ValidateImage(IDocument document, int position, string path, int width, int height)
        {
            CDocumentItem item = document.GetItem(position);
            IImage? image = item.Image;
            if (image == null) return false;
            if (image.Width != width) return false;
            if (image.Height != height) return false;
            if (image.RefPath != path) return false;
            return true;
        }

    }

    public class ParagraphTest
    {
        [Theory]
        [InlineData("test", "test")]
        [InlineData("", "")]
        public void ParagraphConstructorTest(string require, string text)
        {
            CParagraph paragraph = new(text);
            Assert.Equal(require, paragraph.Text);
        }

        [Theory]
        [InlineData("test", "test")]
        [InlineData("", "")]
        public void ParagraphSetTest(string require, string text)
        {
            IParagraph paragraph = new CParagraph("AAAAAAAAAAAAAAAAAAAAAAA")
            {
                Text = text
            };
            Assert.Equal(require, paragraph.Text);
        }
    }

    public class ImageTests
    {
        [Theory]
        [InlineData(100, 100)]
        [InlineData(0, 0)]
        public void ConstructorTests(int width, int height)
        {
            IImage image = new CImage("C:/DEV/test.jpg", "images/img0.jpg", width, height);

            Assert.Equal(width, image.Width);
            Assert.Equal(height, image.Height);
        }

        [Theory]
        [InlineData(100, 100)]
        [InlineData(0, 0)]
        public void ResizeTests(int width, int height)
        {
            IImage image = new CImage("C:/DEV/test.jpg", "images/img0.jpg", 0, 0);

            image.Resize(width, height);

            Assert.Equal(width, image.Width);
            Assert.Equal(height, image.Height);
        }

        [Theory]
        [InlineData(-100, -100)]
        [InlineData(-10, 10)]
        [InlineData(10, -10)]
        public void NegativeConstructorTest(int width, int height)
        {
            Assert.Throws<ArgumentException>(() => new CImage("C:/DEV/test.jpg", "images/img0.jpg", width, height));
        }

        [Theory]
        [InlineData(-100, -100)]
        [InlineData(-10, 10)]
        [InlineData(10, -10)]
        public void NegativeResizeTest(int width, int height)
        {
            IImage image = new CImage("C:/DEV/test.jpg", "images/img0.jpg", 0, 0);

            Assert.Throws<ArgumentException>(() => image.Resize(width, height));
        }
    }

    public class DocumentItemTests
    {

        [Fact]
        public void ItemConstructorParagraphTest()
        {
            CDocumentItem item = new(new CParagraph("test"));

            Assert.True(item.Paragraph != null);
            Assert.False(item.Image != null);
        }

        [Fact]
        public void ItemConstructorImageTest()
        {
            CDocumentItem item = new(new CImage("", "", 100, 100));

            Assert.False(item.Paragraph != null);
            Assert.True(item.Image != null);
        }
    }

    [CollectionDefinition("Document generator")]
    public class DocumentTestsDefinition : ICollectionFixture<CDocument> { }

    [Collection("Document generator")]
    public class DocumentTests : IClassFixture<CDocument>
    {
        private readonly IDocument _document;

        public DocumentTests()
        {
            _document = new CDocument();
        }

        [Fact]
        public void GetTitleTest()
        {
            Assert.Equal(String.Empty, _document.Title);
        }

        [Theory]
        [InlineData("", "")]
        [InlineData("test", "test")]
        [InlineData("Another test", "Another test")]
        public void SetTitleAndGetTest(string require, string title)
        {
            _document.SetTitle(title);

            Assert.Equal(require, _document.Title);
        }

        [Fact]
        public void InsertParagraphTest()
        {
            _document.InsertParagraph("hello", null);
            Assert.Equal(1, _document.GetItemsCount());
            Assert.True(Validator.ValidateParagraph(_document, 0, "hello"));
        }

        [Fact]
        public void InsertImageTest()
        {
            _document.InsertImage("C:/DEV/test.jpg", 100, 200, null);
            Assert.Equal(1, _document.GetItemsCount());
            Assert.True(Validator.ValidateImage(_document, 0, "C:/DEV/test.jpg", 100, 200));
        }

        [Fact]
        public void InsetALittleImages()
        {
            _document.InsertImage("C:/DEV/test.jpg", 100, 200, 0);
            _document.InsertImage("C:/DEV/test.jpg", 200, 100, 0);

            Assert.Equal(2, _document.GetItemsCount());
            Assert.True(Validator.ValidateImage(_document, 0, "C:/DEV/test.jpg", 200, 100));
            Assert.True(Validator.ValidateImage(_document, 1, "C:/DEV/test.jpg", 100, 200));
        }

        [Fact]
        public void InsetALittleParagraphs()
        {
            _document.InsertParagraph("One", 0);
            _document.InsertParagraph("Two", 0);

            Assert.Equal(2, _document.GetItemsCount());
            Assert.True(Validator.ValidateParagraph(_document, 0, "Two"));
            Assert.True(Validator.ValidateParagraph(_document, 1, "One"));
        }

        [Theory]
        [InlineData("Two", 1, 1)]
        [InlineData("One", 1, 0)]
        public void DeleteItemTest(string requireText, int requireCount, int position)
        {
            _document.InsertParagraph("One", 0);
            _document.InsertParagraph("Two", 0);
            _document.DeleteItem(position);

            Assert.Equal(requireCount, _document.GetItemsCount());
            Assert.True(Validator.ValidateParagraph(_document, 0, requireText));
        }

        [Fact]
        public void OutOfRangePositionDeleteTest()
        {
            Assert.Throws<IndexOutOfRangeException>(() => _document.DeleteItem(-1));
            Assert.Throws<IndexOutOfRangeException>(() => _document.DeleteItem(1));
        }
    }

    [Collection("Document generator")]
    public class HistoryTests : IClassFixture<CDocument>
    {
        private readonly IDocument _document;

        public HistoryTests()
        {
            _document = new CDocument();
        }

        [Fact]
        public void AddAndExecuteCommand()
        {
            _document.SetTitle("1 ");
            Assert.True(_document.CanUndo());
            Assert.Equal("1 ", _document.Title);
        }

        [Fact]
        public void UndoTest()
        {
            _document.SetTitle("1 ");
            _document.Undo();

            Assert.False(_document.CanUndo());
            Assert.Equal("", _document.Title);
        }


        [Fact]
        public void DeepMemoryTest()
        {
            _document.SetTitle("1 ");
            _document.SetTitle("2 ");
            _document.SetTitle("3 ");
            _document.SetTitle("4 ");
            _document.SetTitle("5 ");
            _document.SetTitle("6 ");
            _document.SetTitle("7 ");
            _document.SetTitle("8 ");
            _document.SetTitle("9 ");
            _document.SetTitle("10 ");
            _document.SetTitle("11 ");
            _document.SetTitle("12 ");
            _document.Undo();
            _document.Undo();
            _document.Undo();
            _document.Undo();
            _document.Undo();
            _document.Undo();
            _document.Undo();
            _document.Undo();
            _document.Undo();
            _document.Undo();
            _document.Undo();
            _document.Undo();


            Assert.False(_document.CanUndo());
            Assert.Equal("2 ", _document.Title);
        }

        [Fact]
        public void HistoryStandartState()
        {
            Assert.False(_document.CanUndo());
            Assert.False(_document.CanRedo());
        }
    }

    [Collection("Document generator")]
    public class CommandTest : IClassFixture<CDocument>
    {
        private CMenu _menu = new(Console.In, Console.Out);

        private readonly CDocument _document;

        public CommandTest()
        {
            _document = new CDocument();
        }

        [Theory]
        [InlineData("title test", "test ")]
        [InlineData("title test test", "test test ")]
        public void SetTitleCommand(string command, string require)
        {
            var sr = new StringReader($"{command}\nexit\n");
            var sw = new StringWriter();

            _menu = new CMenu(sr, sw);

            _menu.AddItem("title", "", (_1) => DocumentController.SetTitle(_document, _1));
            _menu.AddItem("exit", "", _menu.Exit);

            _menu.Run();

            Assert.Equal(require, _document.Title);
            _document.Undo();
            Assert.Equal("", _document.Title);
            _document.Redo();
            Assert.Equal(require, _document.Title);
        }

        [Fact]
        public void SetTitleNoArguments()
        {
            var sr = new StringReader($"title\nexit\n");
            var sw = new StringWriter();

            _menu = new CMenu(sr, sw);

            _menu.AddItem("title", "", (_1) => DocumentController.SetTitle(_document, _1));
            _menu.AddItem("exit", "", _menu.Exit);

            _menu.Run();

            bool result = sw.ToString().Contains("Invalid arguments count");

            Assert.True(result);
        }

        [Theory]
        [InlineData("ip 0 ABC", "ABC ")]
        [InlineData("ip end ABC", "ABC ")]
        [InlineData("ip 0 ABC ABC", "ABC ABC ")]
        [InlineData("ip end ABC ABC", "ABC ABC ")]
        public void InsertParagraph(string command, string require)
        {
            var sr = new StringReader($"{command}\nexit\n");
            var sw = new StringWriter();

            _menu = new CMenu(sr, sw);

            _menu.AddItem("ip", "", (_1) => DocumentController.InsertParagraph(_document, _1));
            _menu.AddItem("exit", "", _menu.Exit);

            _menu.Run();

            Assert.Equal(require, _document.GetItem(0).Paragraph?.Text);
            _document.Undo();
            Assert.Equal(0, _document.GetItemsCount());
            _document.Redo();
            Assert.Equal(1, _document.GetItemsCount());
            Assert.Equal(require, _document.GetItem(0).Paragraph?.Text);
        }

        [Fact]
        public void InsertParagraphNoArguments()
        {
            var sr = new StringReader($"ip\nexit\n");
            var sw = new StringWriter();

            _menu = new CMenu(sr, sw);

            _menu.AddItem("ip", "", (_1) => DocumentController.InsertParagraph(_document, _1));
            _menu.AddItem("exit", "", _menu.Exit);

            _menu.Run();

            bool result = sw.ToString().Contains("Invalid arguments count");

            Assert.True(result);

        }

        [Theory]
        [InlineData("ii 0 100 100 C:/DEV/test.jpg")]
        [InlineData("ii end 100 100 C:/DEV/test.jpg")]
        public void InsertImage(string command)
        {
            var sr = new StringReader($"{command}\nexit\n");
            var sw = new StringWriter();

            _menu = new CMenu(sr, sw);

            _menu.AddItem("ii", "", (_1) => DocumentController.InsertImage(_document, _1));
            _menu.AddItem("exit", "", _menu.Exit);

            _menu.Run();

            Assert.True(Validator.ValidateImage(_document, 0, "C:/DEV/test.jpg", 100, 100));
            _document.Undo();
            Assert.Equal(0, _document.GetItemsCount());
            _document.Redo();
            Assert.Equal(1, _document.GetItemsCount());
            Assert.True(Validator.ValidateImage(_document, 0, "C:/DEV/test.jpg", 100, 100));
        }

        [Theory]
        [InlineData("ii 0 100 100", "Invalid arguments count")]
        [InlineData("ii 0 100", "Invalid arguments count")]
        [InlineData("ii 0", "Invalid arguments count")]
        [InlineData("ii", "Invalid arguments count")]
        public void InsertImageNoArguments(string command, string require)
        {
            var sr = new StringReader($"{command}\nexit\n");
            var sw = new StringWriter();

            _menu = new CMenu(sr, sw);

            _menu.AddItem("ii", "", (_1) => DocumentController.InsertImage(_document, _1));
            _menu.AddItem("exit", "", _menu.Exit);

            _menu.Run();

            bool result = sw.ToString().Contains(require);

            Assert.True(result);
        }

        [Theory]
        [InlineData("undo")]
        [InlineData("undo\nundo")]
        public void UndoTest(string command)
        {
            _document.SetTitle("test ");

            var sr = new StringReader($"{command}\nexit\n");
            var sw = new StringWriter();

            _menu = new CMenu(sr, sw);

            _menu.AddItem("undo", "", (_1) => DocumentController.Undo(_document, _1));
            _menu.AddItem("exit", "", _menu.Exit);

            _menu.Run();

            Assert.Equal("", _document.Title);
        }

        [Theory]
        [InlineData("redo")]
        [InlineData("redo\nredo")]
        public void RedoTest(string command)
        {
            _document.SetTitle("test ");
            _document.Undo();

            var sr = new StringReader($"{command}\nexit\n");
            var sw = new StringWriter();

            _menu = new CMenu(sr, sw);

            _menu.AddItem("redo", "", (_1) => DocumentController.Redo(_document, _1));
            _menu.AddItem("exit", "", _menu.Exit);

            _menu.Run();

            Assert.Equal("test ", _document.Title);
        }

        [Theory]
        [InlineData("rpt 0 new", "new")]
        [InlineData("rpt 0 new text", "new text")]
        public void ReplaceText(string command, string require)
        {
            _document.InsertParagraph("ad");
            
            var sr = new StringReader($"{command}\nexit\n");
            var sw = new StringWriter();

            _menu = new CMenu(sr, sw);

            _menu.AddItem("rpt", "", (_1) => DocumentController.ReplaceText(_document, _1));
            _menu.AddItem("exit", "", _menu.Exit);

            _menu.Run();

            Assert.Equal(require, _document.GetItem(0).Paragraph?.Text);
        }

        [Theory]
        [InlineData("ris 0 200 100", 100, 200)]
        [InlineData("ris 0 500 0", 0, 500)]
        public void ResizeImage(string command, int requireheight, int requireWidth)
        {
            _document.InsertImage("C:/DEV/test.jpg", 5, 5);

            var sr = new StringReader($"{command}\nexit\n");
            var sw = new StringWriter();

            _menu = new CMenu(sr, sw);

            _menu.AddItem("ris", "", (_1) => DocumentController.ResizeImage(_document, _1));
            _menu.AddItem("exit", "", _menu.Exit);

            _menu.Run();

            Assert.True(Validator.ValidateImage(_document, 0, "C:/DEV/test.jpg", requireWidth, requireheight));
        }
    }
}
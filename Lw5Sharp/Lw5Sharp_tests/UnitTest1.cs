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
            CParagraph paragraph = new CParagraph(text);
            Assert.Equal(require, paragraph.Text);
        }

        [Theory]
        [InlineData("test", "test")]
        [InlineData("", "")]
        public void ParagraphSetTest(string require, string text)
        {
            IParagraph paragraph = new CParagraph("AAAAAAAAAAAAAAAAAAAAAAA");
            paragraph.Text = text;
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
            CDocumentItem item = new CDocumentItem(new CParagraph("test"));

            Assert.True(item.Paragraph != null);
            Assert.False(item.Image != null);
        }

        [Fact]
        public void ItemConstructorImageTest()
        {
            CDocumentItem item = new CDocumentItem(new CImage("", "", 100, 100));

            Assert.False(item.Paragraph != null);
            Assert.True(item.Image != null);
        }
    }

    public class DocumentTests
    {
        private IDocument _document { get; set; }  = new CDocument();

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
            _document.Title = title;

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
            Assert.True(Validator.ValidateImage(_document, 1, "C:/ DEV / test.jpg", 100, 200));
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

    public class HistoryTests
    {
        private IDocument _document { get; set; } = new CDocument();

        [Fact]
        public void AddAndExecuteCommand()
        {
            _document.BuildStrategy = new CSetTitleStrategy();
            _document.BuildAndSendToHistory(new string[] { "1" });
            Assert.True(_document.CanUndo());
            Assert.Equal("1 ", _document.Title);
        }

        [Fact]
        public void UndoTest()
        {
            _document.BuildStrategy = new CSetTitleStrategy();
            _document.BuildAndSendToHistory(new string[] { "1" });
            _document.Undo();

            Assert.False(_document.CanUndo());
            Assert.True(_document.CanRedo());
            Assert.Equal("", _document.Title);
        }


        [Fact]
        public void DeepMemoryTest()
        {
            _document.BuildStrategy = new CSetTitleStrategy();
            _document.BuildAndSendToHistory(new string[] { "1" });
            _document.BuildAndSendToHistory(new string[] { "2" });
            _document.BuildAndSendToHistory(new string[] { "3" });
            _document.BuildAndSendToHistory(new string[] { "4" });
            _document.BuildAndSendToHistory(new string[] { "5" });
            _document.BuildAndSendToHistory(new string[] { "6" });
            _document.BuildAndSendToHistory(new string[] { "7" });
            _document.BuildAndSendToHistory(new string[] { "8" });
            _document.BuildAndSendToHistory(new string[] { "9" });
            _document.BuildAndSendToHistory(new string[] { "10" });
            _document.BuildAndSendToHistory(new string[] { "11" });
            _document.BuildAndSendToHistory(new string[] { "12" });
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
            Assert.True(_document.CanRedo());
            Assert.Equal("2 ", _document.Title);
        }

        [Fact]
        public void HistoryStandartState()
        {
            Assert.False(_document.CanUndo());
            Assert.False(_document.CanRedo());
        }
    }

    public class CommandTest
    {
        private IDocument d { get; set; } = new CDocument();
        private CMenu _menu { get; set; }

        private void LearnMenu(CMenu m)
        {
            m.AddItem("help", "Show all instructions", new CHelpCommand(m));
            m.AddItem("exit", "Exit from programm", new CExitCommand(m));
            m.AddItem("title", "Set new title for document                      <newTitle>", new CSetTitleCommand(d));
            m.AddItem("list", "Show info about document", new CListCommand(d, Console.Out));
            m.AddItem("undo", "Cancels the last action", new CUndoCommand(d));
            m.AddItem("redo", "Restores the canceled action", new CRedoCommand(d));
            m.AddItem("ip", "Inserts a paragraph in the appropriate position    <position>|end <text>", new CInsertParagraphCommand(d));
            m.AddItem("ii", "Inserts a image in the appropriate position        <position>|end <width> <height> <path>", new CInsertImageCommand(d));
            m.AddItem("rpt", "Replace paragraph text                            <position> <newText>", new CReplaceTextCommand(d));
            m.AddItem("ris", "Resize image                                      <position> <newWidth> <newHeight>", new CResizeImageCommand(d));
            m.AddItem("del", "Delete item from position                         <position>", new CDeleteItemCommand(d));
            m.AddItem("save", "Save html document                               <FilePath>", new CSaveCommand(d));
        }

        const string HELP_COMMAND_OUTPUT = "Command list:\r\n" +
                "\thelp: Show all instructions\r\n" +
                "\texit: Exit from programm\r\n" +
                "\ttitle: Set new title for document                      <newTitle>\r\n" +
                "\tlist: Show info about document\r\n\tundo: Cancels the last action\r\n" +
                "\tredo: Restores the canceled action\r\n" +
                "\tip: Inserts a paragraph in the appropriate position    <position>|end <text>\r\n" +
                "\tii: Inserts a image in the appropriate position        <position>|end <width> <height> <path>\r\n" +
                "\trpt: Replace paragraph text                            <position> <newText>\r\n" +
                "\tris: Resize image                                      <position> <newWidth> <newHeight>\r\n" +
                "\tdel: Delete item from position                         <position>\r\n" +
                "\tsave: Save html document                               <FilePath>\r\n>";


        [Fact]
        public void ExitCommandTest()
        {
            var sr = new StringReader("exit\n");
            var sw = new StringWriter();
            _menu = new CMenu(sr, sw);

            LearnMenu(_menu);
            _menu.Run();
            Assert.Equal(HELP_COMMAND_OUTPUT, sw.ToString());
        }

        [Fact]
        public void HelpCommandTest()
        {
            var sr = new StringReader("help\nexit\n");
            var sw = new StringWriter();
            _menu = new CMenu(sr, sw);

            LearnMenu(_menu);
            _menu.Run();
            Assert.Equal(HELP_COMMAND_OUTPUT + HELP_COMMAND_OUTPUT, sw.ToString());
        }

        [Fact]
        public void SetTitleCommandTest()
        {
            var sr = new StringReader("title test test\nexit\n");
            var sw = new StringWriter();
            _menu = new CMenu(sr, sw);
            LearnMenu(_menu);
            _menu.Run();


            Assert.Equal(">", sw.ToString().Replace(HELP_COMMAND_OUTPUT, ""));
            Assert.Equal("test test ", d.Title);
        }

        [Fact]
        public void InsertParagraphCommandTest()
        {
            var sr = new StringReader("list\nip end text\nip end text2\nlist\nexit\n");
            var sw = new StringWriter();
            _menu = new CMenu(sr, sw);

            LearnMenu(_menu);
            _menu.Run();

            Assert.Equal(2, d.GetItemsCount());
        }

        [Fact]
        public void InsertImageCommandTest()
        {
            var sr = new StringReader("list\nii end 100 100 C:/DEV/test.jpg\nii end 100 100 C:/DEV/test.jpg\nlist\nexit\n");
            var sw = new StringWriter();
            _menu = new CMenu(sr, sw);

            LearnMenu(_menu);
            _menu.Run();

            Assert.Equal(2, d.GetItemsCount());
        }

        [Fact]
        public void ReplaceTextCommandTest()
        {
            var sr = new StringReader("ip end text\nrpt 0 test\nexit\n");
            var sw = new StringWriter();
            _menu = new CMenu(sr, sw);

            LearnMenu(_menu);
            _menu.Run();

            Assert.Equal(1, d.GetItemsCount());
            Assert.Equal("test ", d.GetItem(0).Paragraph?.Text);
        }

        [Fact]
        public void ResizeImageCommandTest()
        {
            var sr = new StringReader("ii end 100 100 C:/DEV/test.jpg\nris 0 200 200\nexit\n");
            var sw = new StringWriter();
            _menu = new CMenu(sr, sw);

            LearnMenu(_menu);
            _menu.Run();

            Assert.Equal(1, d.GetItemsCount());
            Assert.True(Validator.ValidateImage(d, 0, "C:/DEV/test.jpg", 200, 200));
        }

        [Theory]
        [InlineData("", "undo\n")]
        [InlineData("ABOBA ", "undo\nredo\n")]
        public void UndoRedoCommandTest(string requireTitle, string command)
        {
            var sr = new StringReader($"title ABOBA\n{command}exit\n");
            var sw = new StringWriter();
            _menu = new CMenu(sr, sw);

            LearnMenu(_menu);
            _menu.Run();

            Assert.Equal(requireTitle, d.Title);
        }

        [Fact]
        public void DelCommandTest()
        {
            var sr = new StringReader($"ip end title\ndel 0\nexit\n");
            var sw = new StringWriter();
            _menu = new CMenu(sr, sw);

            LearnMenu(_menu);
            _menu.Run();

            Assert.Equal(0, d.GetItemsCount());
        }

        [Fact]
        public void SaveCommandTest()
        {
            var sr = new StringReader($"ip end paragraph\ntitle TITLE\nii end 100 100 C:/DEV/test.jpg\nsave C:/DEV/index.html\nexit\n");
            var sw = new StringWriter();
            _menu = new CMenu(sr, sw);

            LearnMenu(_menu);
            _menu.Run();

            using (StreamReader reader = new StreamReader("C:/DEV/index.html"))
            {

                string result = reader.ReadToEnd();
                Assert.Equal("<html>\r\n" +
                    "<h1>TITLE </h1>\r\n" +
                    "<p>paragraph </p>\r\n" +
                    "<img src=\"images/img0.jpg\" width=\"100\" height=\"100\"/ >\r\n" +
                    "</html>\r\n", result);
            }
        }
    }
}
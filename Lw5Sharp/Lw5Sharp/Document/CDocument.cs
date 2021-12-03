using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Assertion;

namespace Document
{
    internal class CDocument : IDocument
    {


        public string Title { get; set; } = string.Empty;        
        private CHistory _history = new CHistory();
        private List<CDocumentItem> _items = new List<CDocumentItem>();
        private const string IMAGE_FOLDER_NAME = "images";
        private int _imageCount = 0;

        public CDocument()
        {
            if (Directory.Exists(IMAGE_FOLDER_NAME))
                Directory.Delete(IMAGE_FOLDER_NAME, true);

            Directory.CreateDirectory(IMAGE_FOLDER_NAME);
        }

        public bool CanRedo() => _history.CanRedo();

        public bool CanUndo() => _history.CanUndo();

        public void DeleteItem(int index)
        {
            _history.AddAndExecuteCommand(new RemoveItemCommand(_items, index));
        }

        public CDocumentItem GetItem(int index)
        {
            if (index >= GetItemsCount() || index < 0)
                throw new IndexOutOfRangeException("Index out of range");

            return _items[index];
        }

        public int GetItemsCount()
        {
            return _items.Count;
        }

        public IImage InsertImage(string path, int width, int heigh, int? position = null)
        {

            Assert.AssertionPath(path);

            string extension = Path.GetExtension(path); 
            string documentPath = $"{IMAGE_FOLDER_NAME}/img{_imageCount++}{extension}";

            CImage image = new CImage(path, documentPath, width, heigh);

            _history.AddAndExecuteCommand(new InsertItemCommand(
                _items,
                new CDocumentItem(image), 
                (position == null) ? _items.Count : position.Value
                ));

            return image;
        }

        public IParagraph InsertParagraph(string text, int? position = null)
        {
            CParagraph paragraph = new CParagraph(text);

            _history.AddAndExecuteCommand(new InsertItemCommand(
                _items,
                new CDocumentItem(paragraph), 
                (position == null) ? _items.Count : position.Value)
            );

            return paragraph;
        }

        public void Redo() => _history.Redo();

        public void Undo() => _history.Undo();

        public void Save(string path)
        {
            using (StreamWriter sr = new StreamWriter(path))
            {
                sr.WriteLine("<html>");
                sr.WriteLine($"<h1>{HtmlParser.ParseHtmlString(Title)}</h1>");

                _items.ForEach(item =>
                {
                    IParagraph? paragraph = item.Paragraph;
                    IImage? image = item.Image;
                    if (image != null)
                        sr.WriteLine($"<img " +
                            $"src=\"{HtmlParser.ParseHtmlString(image.DocumentPath)}\" " +
                            $"width=\"{image.Width}\" " +
                            $"height=\"{image.Height}\"/ >"
                        );

                    if (paragraph != null)
                        sr.WriteLine($"<p>{HtmlParser.ParseHtmlString(paragraph.Text)}</p>");
                });
                sr.WriteLine("</html>");
            }

            string saveFolder = path.Substring(0, path.LastIndexOf('/'));

            Directory.CreateDirectory($"{saveFolder}/{IMAGE_FOLDER_NAME}");
            string[] images = Directory.GetFileSystemEntries(IMAGE_FOLDER_NAME);
            foreach (string file in images)
                File.Copy(file, $"{saveFolder}/{IMAGE_FOLDER_NAME}/{Path.GetFileName(file)}", true);
        }

        public void ShowCurrentState(TextWriter output)
        {
            output.WriteLine($"Title: {Title}");
            for (int i = 0; i < _items.Count(); ++i)
            {
                var item = _items[i];
                output.WriteLine($"{i}. {item.GetItemInfo()}");
            }
        }

        public void SetTitle(string title)
        {
            _history.AddAndExecuteCommand(new SetTitleCommand(this, Title, title));   
        }

        public void ReplaceText(int position, string text)
        {
            Assert.AssertionPosition(position, _items.Count());

            _history.AddAndExecuteCommand(new ReplaceTextCommand(
                _items,
                position,
                text,
                _items[position].Paragraph?.Text ?? throw new Exception("Invalid paragraph")));

        }

        public void ResizeImage(int position, int width, int height)
        {
            _history.AddAndExecuteCommand(new ResizeImageCommand(_items, position, width, height));
        }
    }
}

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Document
{
    internal class CDocument : IDocument
    {
        public string Title { get; set; } = string.Empty;
        public ICommadBuildStrategy? BuildStrategy { private get; set; } = null;
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
            if (index >= GetItemsCount() || index < 0)
                throw new IndexOutOfRangeException("Index out of range");

            IImage? item = _items[index].Image;
            if (item != null)
            {
                File.Delete(item.DocumentPath);
            }

            _items.RemoveAt(index);
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

            if (!File.Exists(path))
                throw new Exception("File is not exists");

            string extension = Path.GetExtension(path); 
            string documentPath = $"{IMAGE_FOLDER_NAME}/img{_imageCount++}{extension}";

            CImage image = new CImage(path, documentPath, width, heigh);

            File.Copy(path, documentPath);

            if (position == null || GetItemsCount() == 0 && position == 0)
            {
                _items.Add(new CDocumentItem(image));
            }
            else
            {
                if (position >= GetItemsCount())
                    throw new IndexOutOfRangeException("Index out of range");

                _items.Insert((int)position, new CDocumentItem(image));

            }
            
            return image;
        }

        public IParagraph InsertParagraph(string text, int? position = null)
        {
            CParagraph paragraph = new CParagraph(text);

            Console.WriteLine(position);

            if (position == null || GetItemsCount() == 0 && position == 0)
            {
                _items.Add(new CDocumentItem(paragraph));
            }
            else
            {
                if (position >= GetItemsCount())
                    throw new IndexOutOfRangeException("Index out of range");

                _items.Insert((int)position, new CDocumentItem(paragraph));
            }

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

        public void BuildAndSendToHistory(string[]? args)
        {
            if (BuildStrategy == null)
                return;

            CAbstractCommand command = BuildStrategy.BuildCommand(this, args);
            _history.AddAndExecuteCommand(command);
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
    }
}

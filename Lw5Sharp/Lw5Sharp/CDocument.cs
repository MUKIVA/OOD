using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CDocument : IDocument
    {
        public string Title { get; set; } = string.Empty;
        public ICommadBuildStrategy? BuildStrategy { private get; set; } = null;
        private CHistory _history = new CHistory();
        private List<CDocumentItem> _items = new List<CDocumentItem>();

        public bool CanRedo() => _history.CanRedo();

        public bool CanUndo() => _history.CanUndo();

        public void DeleteItem(int index)
        {
            if (index >= GetItemsCount() || index < 0)
                throw new IndexOutOfRangeException("Index out of range");

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
            CImage image = new CImage(path, width, heigh);

            if (position == null)
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

            if (position == null)
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
            throw new NotImplementedException();
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

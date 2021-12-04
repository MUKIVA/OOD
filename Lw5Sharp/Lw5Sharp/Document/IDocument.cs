
using System.IO;

namespace Document
{
    public interface IDocument
    {
        public string Title { get; set; }

        void ShowCurrentState(TextWriter output);
        IParagraph InsertParagraph(string text, int? position = null);
        IImage InsertImage(string path, int width, int heigh, int? position = null);

        CDocumentItem GetItem(int index);

        void DeleteItem(int index);

        void SetTitle(string title);
        void ReplaceText(int position, string text);
        void ResizeImage(int position, int width, int height);

        bool CanUndo();
        void Undo();
        bool CanRedo();
        void Redo();

        void Save(string path);
        
        int GetItemsCount();
    }
}

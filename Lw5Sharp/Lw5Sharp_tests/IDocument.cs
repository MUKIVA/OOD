
using System.IO;

namespace Document
{
    internal interface IDocument
    {
        public string Title { get; set; }
        public ICommadBuildStrategy BuildStrategy { set; }

        void ShowCurrentState(TextWriter output);

        IParagraph InsertParagraph(string text, int? position = null);
        IImage InsertImage(string path, int width, int heigh, int? position = null);

        CDocumentItem GetItem(int index);

        void DeleteItem(int index);

        bool CanUndo();
        void Undo();
        bool CanRedo();
        void Redo();

        void Save(string path);
        
        int GetItemsCount();

        void BuildAndSendToHistory(string[]? args);
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    public class DocumentController
    {
        private readonly CDocument _document = new();
        private readonly CMenu _menu;

        public DocumentController(TextReader input, TextWriter output)
        {
            _menu = new CMenu(input, output);
            _menu.AddItem("help", "Show all instructions", _menu.ShowInstructions);
            _menu.AddItem("exit", "Exit from programm", _menu.Exit);
            _menu.AddItem("title", "Set new title for document                      <newTitle>", (_1) => SetTitle(_document, _1));
            _menu.AddItem("list", "Show info about document", (_1) => ShowList(_document, output, _1));
            _menu.AddItem("undo", "Cancels the last action", (_1) => Undo(_document, _1));
            _menu.AddItem("redo", "Restores the canceled action", (_1) => Redo(_document, _1));
            _menu.AddItem("ip", "Inserts a paragraph in the appropriate position    <position>|end <text>", (_1) => InsertParagraph(_document, _1));
            _menu.AddItem("ii", "Inserts a image in the appropriate position        <position>|end <width> <height> <path>", (_1) => InsertImage(_document, _1));
            _menu.AddItem("rpt", "Replace paragraph text                            <position> <newText>", (_1) => ReplaceText(_document, _1));
            _menu.AddItem("ris", "Resize image                                      <position> <newWidth> <newHeight>", (_1) => ResizeImage(_document, _1));
            _menu.AddItem("del", "Delete item from position                         <position>", (_1) => DeleteItem(_document, _1));
            _menu.AddItem("save", "Save html document                               <FilePath>", (_1) => SaveDocument(_document, _1));
        }

        public void Start()
        {
            _menu.Run();
        }

        public int DocumentItemCount()
        {
            return _document.GetItemsCount();
        }

        public static void SetTitle(IDocument document, string[]? args = null)
        {
            if (args == null || args.Length < 1)
                throw new ArgumentException("Invalid arguments count");

            string text = "";
            for (int i = 0; i < args.Length; ++i) text += $"{args[i]} ";

            document.SetTitle(text);
        }
        public static void ShowList(IDocument document, TextWriter output, string[]? args = null)
        {
            if (document is null)
            {
                throw new ArgumentNullException(nameof(document));
            }

            if (output is null)
            {
                throw new ArgumentNullException(nameof(output));
            }

            document.ShowCurrentState(output);
        }
        public static void Undo(IDocument document, string[]? args = null)
        {
            document.Undo();
        }
        public static void Redo(IDocument document, string[]? args = null)
        {
            document.Redo();
        }
        public static void InsertParagraph(IDocument document, string[]? args = null)
        {
            if (args == null || args.Length < 2)
                throw new ArgumentException("Invalid arguments count");

            if (!int.TryParse(args[0], out int parsedPosition) && args[0] != "end")
                throw new ArgumentException("Failed parse to a position");

            string text = "";
            for (int i = 1; i < args.Length; ++i) text += $"{args[i]} ";

            document.InsertParagraph(text, args[0] == "end" ? null : parsedPosition);
        }
        public static void InsertImage(IDocument document, string[]? args = null)
        {
            if (args == null || args.Length < 4)
                throw new ArgumentException("Invalid arguments count");


            if (!int.TryParse(args[0], out int parsedPosition) && args[0] != "end")
                throw new ArgumentException("Failed parse to a position");

            if (!int.TryParse(args[1], out int width) || !int.TryParse(args[2], out int height))
                throw new ArgumentException("Failed parse to a image resolution");

            document.InsertImage(args[3], width, height, (args[0] == "end") ? null : parsedPosition);
        }
        public static void ReplaceText(IDocument document, string[]? args = null)
        {
            if (args == null || args.Length < 2)
                throw new ArgumentException("Invalid arguments count");

            if (!int.TryParse(args[0], out int position))
                throw new ArgumentException("Invalid position for replace");

            string text = "";
            for (int i = 1; i < args.Length; ++i) text += $"{args[i]} ";

            document.ReplaceText(position, text);
        }
        public static void ResizeImage(IDocument document, string[]? args = null)
        {
            if (args == null || args.Length < 3)
                throw new ArgumentException("Invalid arguments count");

            if (!int.TryParse(args[0], out int position))
                throw new ArgumentException("Invalid position for resize");

            if (!int.TryParse(args[1], out int width) || !int.TryParse(args[2], out int height))
                throw new ArgumentException("Ivalid height or width value");

            document.ResizeImage(position, width, height);
        }
        public static void DeleteItem(IDocument document, string[]? args = null)
        {
            if (args == null || args.Length < 1)
                throw new ArgumentException("Invalid arguments count");

            if (!int.TryParse(args[0], out int position))
                throw new ArgumentException("Invalid position for resize");

            document.DeleteItem(position);
        }
        public static void SaveDocument(IDocument document, string[]? args = null)
        {
            if (args == null || args.Length < 1)
                throw new ArgumentException("Invalid arguments count");

            document.Save(args[0]);
        }
    }
}

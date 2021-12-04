using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    public class CMenu
    {
        private TextReader _input { get; set; }
        private TextWriter _output { get; set; }
        private List<Item> _items = new List<Item>();
        private bool _exit = false;
        public delegate void CommandDelegate(string[]? args = null);

        public CMenu(TextReader input, TextWriter output)
        {
            _input = input;
            _output = output;
        }

        public void AddItem(string shortcut, string description, CommandDelegate command)
        {
            _items.Add(new Item(shortcut, description, command));
        }

        public void Run()
        {
            ShowInstructions();
            do
            {
                try
                {
                    _output.Write('>');
                    ExecuteCommand(_input.ReadLine()?.Split(" "));
                }
                catch (Exception ex)
                {   
                    _output.WriteLine(ex.Message);
                }
            } while (!_exit);
        }

        bool ExecuteCommand(string[]? args = null)
        {
            if (args == null)
                return !_exit;

            args = args.Where(x => !string.IsNullOrWhiteSpace(x)).ToArray();

            string command = args[0];

            int itemNum = _items.FindIndex(item => item.Shortcut == command);

            if (itemNum != -1)
            {
                _items[itemNum].Command(args.Skip(1).ToArray());
            }
            else
            {
                _output.WriteLine("Uncknown command");
            }

            return !_exit;
        }

        public void Exit(string[]? args = null)
        {
            _exit = true;
        }

        public void ShowInstructions(string[]? args = null)
        {
            _output.WriteLine("Command list:");
            _items.ForEach(item => _output.WriteLine($"\t{item.Shortcut}: {item.Description}"));
        }

        private struct Item
        {
                
            public Item(string shortcut, string description, CommandDelegate command)
            {
                Shortcut = shortcut;
                Description = description;
                Command = command;
            }

            public string Shortcut { get; set; }
            public string Description { get; set; }
            public CommandDelegate Command { get; set; }
        }

        public void SetTitle(IDocument document, string[]? args = null)
        {
            if (args == null || args.Count() < 1)
                throw new NullReferenceException("Invalid arguments count");

            string text = "";
            for (int i = 0; i < args.Count(); ++i) text += $"{args[i]} ";

            document.SetTitle(text);
        }

        public void ShowList(IDocument document, string[]? args = null)
        {
            document.ShowCurrentState(_output);
        }

        public void Undo(IDocument document, string[]? args = null)
        {
            document.Undo();
        }

        public void Redo(IDocument document, string[]? args = null)
        {
            document.Redo();
        }

        public void InsertParagraph(IDocument document, string[]? args = null)
        {
            if (args == null || args.Count() < 2)
                throw new NullReferenceException("Invalid arguments count");

            int parsedPosition;

            if (!int.TryParse(args[0], out parsedPosition) && args[0] != "end")
                throw new ArgumentException("Failed parse to a position");

            string text = "";
            for (int i = 1; i < args.Count(); ++i) text += $"{args[i]} ";

            document.InsertParagraph(text, args[0] == "end" ? null : parsedPosition);
        }

        public void InsertImage(IDocument document, string[]? args = null)
        {
            if (args == null || args.Count() < 4)
                throw new NullReferenceException("Invalid arguments count");

            int parsedPosition;
            int width;
            int height;

            if (!int.TryParse(args[0], out parsedPosition) && args[0] != "end")
                throw new ArgumentException("Failed parse to a position");

            if (!int.TryParse(args[1], out width) || !int.TryParse(args[2], out height))
                throw new ArgumentException("Failed parse to a image resolution");

            document.InsertImage(args[3], width, height, (args[0] == "end") ? null : parsedPosition);
        }

        public void ReplaceText(IDocument document, string[]? args = null)
        {
            if (args == null || args.Count() < 2)
                throw new NullReferenceException("Invalid arguments count");

            int position;

            if (!int.TryParse(args[0], out position))
                throw new ArgumentException("Invalid position for replace");

            string text = "";
            for (int i = 1; i < args.Count(); ++i) text += $"{args[i]} ";

            document.ReplaceText(position, text);
        }

        public void ResizeImage(IDocument document, string[]? args = null)
        {
            if (args == null || args.Count() < 3)
                throw new NullReferenceException("Invalid arguments count");

            int position;
            int width;
            int height;

            if (!int.TryParse(args[0], out position))
                throw new ArgumentException("Invalid position for resize");

            if (!int.TryParse(args[1], out width) || !int.TryParse(args[2], out height))
                throw new ArgumentException("Ivalid height or width value");

            document.ResizeImage(position, width, height);
        }

        public void DeleteItem(IDocument document, string[]? args = null)
        {
            if (args == null || args.Count() < 1)
                throw new NullReferenceException("Invalid arguments count");

            int position;

            if (!int.TryParse(args[0], out position))
                throw new ArgumentException("Invalid position for resize");

            document.DeleteItem(position);
        }

        public void SaveDocument(IDocument document, string[]? args = null)
        {
            if (args == null || args.Count() < 1 )
                throw new ArgumentException("Invalid arguments count");

            document.Save(args[0]);
        }
    }
}

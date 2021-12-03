using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CMenu
    {

        private TextReader _input { get; set; }
        private TextWriter _output { get; set; }
        private List<Item> _items = new List<Item>();
        private bool _exit = false;

        public CMenu(TextReader input, TextWriter output)
        {
            _input = input;
            _output = output;
        }

        public void AddItem(string shortcut, string description, ICommand command)
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

        bool ExecuteCommand(string[]? args)
        {
            if (args == null)
                return !_exit;

            args = args.Where(x => !string.IsNullOrWhiteSpace(x)).ToArray();

            string command = args[0];

            int itemNum = _items.FindIndex(item => item.Shortcut == command);

            if (itemNum != -1)
            {
                _items[itemNum].Command.Execute(args.Skip(1).ToArray());
            }
            else
            {
                _output.WriteLine("Uncknown command");
            }

            return !_exit;
        }

        public void Exit()
        {
            _exit = true;
        }

        public void ShowInstructions()
        {
            _output.WriteLine("Command list:");
            _items.ForEach(item => _output.WriteLine($"\t{item.Shortcut}: {item.Description}"));
        }

        private struct Item
        {
            public Item(string shortcut, string description, ICommand command)
            {
                Shortcut = shortcut;
                Description = description;
                Command = command;
            }

            public string Shortcut { get; set; }
            public string Description { get; set; }
            public ICommand Command { get; set; }
        }
    }
}

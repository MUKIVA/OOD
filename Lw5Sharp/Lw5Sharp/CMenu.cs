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
        private TextReader Input { get; set; }
        private TextWriter Output { get; set; }
        private readonly List<Item> _items = new();
        private bool _exit = false;
        public delegate void CommandDelegate(string[]? args = null);

        public CMenu(TextReader input, TextWriter output)
        {
            Input = input;
            Output = output;
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
                    Output.Write('>');
                    ExecuteCommand(Input.ReadLine()?.Split(" "));
                }
                catch (Exception ex)
                {   
                    Output.WriteLine(ex.Message);
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
                Output.WriteLine("Uncknown command");
            }

            return !_exit;
        }

        public void Exit(string[]? args = null)
        {
            _exit = true;
        }

        public void ShowInstructions(string[]? args = null)
        {
            Output.WriteLine("Command list:");
            _items.ForEach(item => Output.WriteLine($"\t{item.Shortcut}: {item.Description}"));
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
    }
}

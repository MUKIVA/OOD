using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task2
{
    internal class Menu
    {
        private TextReader Input { get; set; }
        private TextWriter Output { get; set; }
        private readonly List<Item> _items = new();
        private bool _exit = false;
        public delegate void CommandDelegate();

        public Menu(TextReader input, TextWriter output)
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
                _items[itemNum].Command(); //args.Skip(1).ToArray()
            }
            else
            {
                Output.WriteLine("Uncknown command");
            }

            return !_exit;
        }

        public void Exit()
        {
            _exit = true;
        }

        public void ShowInstructions()
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

        public void CreateMacroCommand()
        {
            MacroCommand macro = new();
            Output.Write("Macro shortcut: ");
            string macroShortcut = Input.ReadLine() ?? throw new Exception("Macro name cannot be empty");
            Output.Write("Macro description: ");
            string macroDesc = Input.ReadLine() ?? "";
            string command = string.Empty;
            ShowInstructions();
            Output.WriteLine("Enter 'q' to exit macro design mode");
            while (command != "q")
            {
                Output.Write('/');
                command = Input.ReadLine() ?? "";
                int itemNum = _items.FindIndex(item => item.Shortcut == command);

                if (itemNum != -1)
                    macro.InsertCommand(() => _items[itemNum].Command());
                else
                    Output.WriteLine((command != "q") ? "Uncknown command" : "");
            }

            AddItem(macroShortcut, macroDesc, () => macro.Execute());
        }
    }
}

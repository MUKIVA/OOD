using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task2
{
    internal class MacroCommand : ICommand
    {
        public delegate void MacroCommandDelegate();

        private readonly List<MacroCommandDelegate> _commands = new();

        public void Execute()
        {
            _commands.ForEach(command => command());
        }

        public void InsertCommand(MacroCommandDelegate @delegate)
        {
            _commands.Add(@delegate);
        }
    }
}

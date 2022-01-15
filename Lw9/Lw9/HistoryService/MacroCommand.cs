using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lw9.HistoryService
{
    public class MacroCommand : IUnduableCommand
    {
        private IUnduableCommand[] _commands;

        public MacroCommand(IUnduableCommand[] commands)
        {
            _commands = commands;
        }

        public void Execute()
        {
            foreach (IUnduableCommand command in _commands)
            {
                command.Execute();
            }
        }

        public void Unexecute()
        {
            for (int i = 1; i <= _commands.Length; ++i)
            {
                _commands[^i].Unexecute();
            }
        }
    }
}

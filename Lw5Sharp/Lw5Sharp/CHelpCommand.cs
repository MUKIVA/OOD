using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CHelpCommand : ICommand
    {
        private CMenu _menu;

        public CHelpCommand(CMenu menu)
        {
            _menu = menu;
        }

        public void Execute(string[]? args)
        {
            _menu.ShowInstructions();
        }

        public void Unexecute()
        {
        }
    }
}

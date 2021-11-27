using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CExitCommand : ICommand
    {
        private CMenu _menu;

        public CExitCommand(CMenu menu)
        { 
            _menu = menu;
        }

        public void Execute(string[]? args)
        {
            _menu.Exit();    
        }

        public void Unexecute()
        {
        }
    }
}

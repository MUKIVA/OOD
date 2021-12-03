using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    abstract class CAbstractCommand : ICommand
    {
        public bool Executed { get; private set; } = false;

        public void Execute(string[]? args = null) 
        {
            if (!Executed)
                DoExecute();
            Executed = true;
        }

        public void Unexecute()
        {
            if (Executed)
                DoUnexecute();
            Executed = false;
        }

        protected abstract void DoExecute();
        protected abstract void DoUnexecute();

    }
}

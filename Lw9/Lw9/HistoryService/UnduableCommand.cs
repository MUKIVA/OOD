using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lw9.HistoryService
{
    public interface IUnduableCommand
    {
        public void Execute();
        public void Unexecute();
    }
}

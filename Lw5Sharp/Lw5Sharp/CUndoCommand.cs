using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CUndoCommand : ICommand
    {
        private IDocument _document;

        public CUndoCommand(IDocument document)
        {
            _document = document;
        }

        public void Execute(string[]? args = null)
        {
            _document.Undo();
        }

        public void Unexecute()
        {
            
        }
    }
}

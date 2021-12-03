using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CRedoCommand : ICommand
    {
        private IDocument _document;

        public CRedoCommand(IDocument document)
        { 
            _document = document;
        }

        public void Execute(string[]? args = null)
        {
            _document.Redo();
        }

        public void Unexecute()
        {
            
        }
    }
}

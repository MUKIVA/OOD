using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CListCommand : ICommand
    {
        private IDocument _document;
        private TextWriter _writer;

        public CListCommand(IDocument document, TextWriter writer)
        {
            _document = document;
            _writer = writer;
        }

        public void Execute(string[]? args = null)
        {
            _document.ShowCurrentState(_writer);
        }

        public void Unexecute()
        {
            throw new NotImplementedException();
        }
    }
}

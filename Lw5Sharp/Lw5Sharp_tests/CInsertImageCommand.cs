using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CInsertImageCommand : ICommand
    {
        private ICommadBuildStrategy _stategy = new CInsertImageStrategy();
        private IDocument _document;

        public CInsertImageCommand(IDocument document)
        {
            _document = document;
        }

        public void Execute(string[]? args = null)
        {
            _document.BuildStrategy = _stategy;
            _document.BuildAndSendToHistory(args);
        }

        public void Unexecute()
        {
        }
    }
}

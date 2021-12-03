using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CReplaceTextCommand : ICommand
    {
        private ICommadBuildStrategy _strategy = new CReplaceTextStrategy();
        private IDocument _document;

        public CReplaceTextCommand(IDocument document)
        {
            _document = document;
        }

        public void Execute(string[]? args = null)
        {
            _document.BuildStrategy = _strategy;
            _document.BuildAndSendToHistory(args);
        }

        public void Unexecute()
        {
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CSaveCommand : ICommand
    {
        private IDocument _document;

        public CSaveCommand(IDocument document)
        {
            _document = document;
        }

        public void Execute(string[]? args = null)
        {
            if (args?.Count() != 1)
                throw new ArgumentException("Invalid arguments count");

            _document.Save(args[0]);
        }

        public void Unexecute()
        {
        }
    }
}

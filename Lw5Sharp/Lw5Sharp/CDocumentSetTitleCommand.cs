using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CDocumentSetTitleCommand : CAbstractCommand
    {
        private IDocument _document;
        private string _oldTitle;
        private string _newTitle;


        public CDocumentSetTitleCommand(IDocument document, string oldTitle, string newTitle)
        {
            _document = document;
            _oldTitle = oldTitle;
            _newTitle = newTitle;
        }

        protected override void DoExecute()
        {
            _document.Title = _newTitle;
        }

        protected override void DoUnexecute()
        {
            _document.Title = _oldTitle;
        }
    }
}

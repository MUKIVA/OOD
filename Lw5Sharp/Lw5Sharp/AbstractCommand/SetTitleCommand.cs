using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class SetTitleCommand : CAbstractCommand
    {
        private IDocument _document;
        private readonly string _newTitle;
        private readonly string _oldTitle;

        public SetTitleCommand(IDocument document, string oldTitile, string newTitle)
        {
            _document = document;
            _oldTitle = oldTitile;
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

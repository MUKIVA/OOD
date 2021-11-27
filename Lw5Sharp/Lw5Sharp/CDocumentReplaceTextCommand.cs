using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CDocumentReplaceTextCommand : CAbstractCommand
    {
        private string _newText;
        private string _oldText;
        private IParagraph _item;

        public CDocumentReplaceTextCommand(IParagraph item ,string newText)
        { 
            _newText = newText;
            _item = item;
            _oldText = _item.Text;
        }

        protected override void DoExecute()
        {
            _item.Text = _newText;
        }

        protected override void DoUnexecute()
        {
            _item.Text = _oldText;
        }
    }
}

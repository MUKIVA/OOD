using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CDocumentInsertParagraphCommand : CAbstractCommand
    {
        private IDocument _document;
        private string _text;
        private int? _position;

        public CDocumentInsertParagraphCommand(IDocument document, string text, int? position)
        {
            _document = document;
            _text = text;
            _position = position;

            if (_position < 0) _position = 0;
        }

        protected override void DoExecute()
        {
            _document.InsertParagraph(_text, _position);
        }

        protected override void DoUnexecute()
        {
            _document.DeleteItem((_position == null) ? _document.GetItemsCount() - 1 : (int)_position);
        }
    }
}

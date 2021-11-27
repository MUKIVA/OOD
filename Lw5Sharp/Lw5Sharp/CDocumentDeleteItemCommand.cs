using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CDocumentDeleteItemCommand : CAbstractCommand
    {
        private IDocument _document;
        private int _position;
        private CDocumentItem _item;

        public CDocumentDeleteItemCommand(IDocument document, int position)
        {
            _document = document;
            _position = position;
            _item = _document.GetItem(position);
        }

        protected override void DoExecute()
        {
            _document.DeleteItem(_position);
        }

        protected override void DoUnexecute()
        {

            if (_item.Image != null)
                _document.InsertImage(_item.Image.RefPath,
                    _item.Image.Width, 
                    _item.Image.Height, 
                    (_position == 0 && _document.GetItemsCount() == 0) ? null : _position);

            if (_item.Paragraph != null)
                _document.InsertParagraph(_item.Paragraph.Text,
                    (_position == 0 && _document.GetItemsCount() == 0) ? null : _position);
        }
    }
}

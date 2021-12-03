using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CDocumentInsertImageCommand : CAbstractCommand
    {
        private IDocument _document;
        private string _path;
        private int _width;
        private int _height;
        private int? _position;

        public CDocumentInsertImageCommand(IDocument document, int? position, int width, int height, string path)
        {
            _document = document;
            _width = width;
            _height = height;
            _path = path;
            _position = position;

            if (_position < 0) _position = 0;
        }

        protected override void DoExecute()
        {
            _document.InsertImage(_path, _width, _height, _position);
        }

        protected override void DoUnexecute()
        {
            _document.DeleteItem((_position == null) ? _document.GetItemsCount() - 1 : (int)_position);
        }
    }
}

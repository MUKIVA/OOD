using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Assertion;

namespace Document
{
    internal class InsertItemCommand : CAbstractCommand
    {
        private readonly int _position;
        private readonly List<CDocumentItem> _items;
        private readonly CDocumentItem _item;
        private readonly string _documentPath = string.Empty;
        private readonly string _path = string.Empty;

        public InsertItemCommand(List<CDocumentItem> items, CDocumentItem item, int position)
        {
            _items = items;
            _item = item;
            _position = position;

            Assert.AssertionPosition(_position, _items.Count());

            if (_item.Image != null)
            {
                _path = _item.Image.RefPath;
                _documentPath = _item.Image.DocumentPath;
            }
        }

        protected override void DoExecute()
        {
            if (_item.Image != null)
            {
                Assert.AssertionPath(_path);
                File.Copy(_path, _documentPath);
            }

            _items.Insert(_position, _item);
        }

        protected override void DoUnexecute()
        {
            if (_item.Image != null)
            {
                Assert.AssertionPath(_documentPath);
                File.Delete(_documentPath);
            }

            _items.RemoveAt(_position);   
        }
    }
}

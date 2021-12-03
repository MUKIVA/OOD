using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Assertion;

namespace Document
{
    internal class RemoveItemCommand : CAbstractCommand
    {
        private readonly List<CDocumentItem> _items;
        private readonly int _position;
        private readonly CDocumentItem _item;
        private readonly string _documentPath = string.Empty;
        private readonly string _path = string.Empty;

        public RemoveItemCommand(List<CDocumentItem> items, int position)
        {
            _position = position;
            _items = items;

            Assert.AssertionPosition(position, items.Count());

            _item = (CDocumentItem)_items[position].Clone();

            if (_item.Image != null)
            {
                _documentPath = _item.Image.DocumentPath;
                _path = _item.Image.RefPath;
            }
        }

        protected override void DoExecute()
        {
            if (_item.Image != null)
            {
                Assert.AssertionPath(_documentPath);
                File.Delete(_documentPath);
            }
            
            _items.RemoveAt(_position);
        }

        protected override void DoUnexecute()
        {
            if (_item.Image != null)
            {
                Assert.AssertionPath(_path);
                File.Copy(_path, _documentPath);
            }

            _items.Insert(_position, _item);
        }
    }
}

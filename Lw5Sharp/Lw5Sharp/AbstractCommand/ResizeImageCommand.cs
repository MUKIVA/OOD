using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Assertion;

namespace Document
{
    public class ResizeImageCommand : CAbstractCommand
    {
        private readonly int _position;
        private readonly List<CDocumentItem> _items;
        private readonly int _newWidth;
        private readonly int _oldWidth;
        private readonly int _newHeight;
        private readonly int _oldHeight;

        private static void AssertImage(CDocumentItem item)
        {
            if (item.Image  == null)
                throw new ArgumentException("Item isn't a paragraph");
        }

        public ResizeImageCommand(List<CDocumentItem> items, int pos, int newWidth, int newHeight)
        {
            _items = items;
            _newWidth = newWidth;
            _newHeight = newHeight;
            _position = pos;

            Assert.AssertionPosition(_position, _items.Count);
            AssertImage(_items[_position]);

            _oldHeight = _items[_position].Image?.Height ?? throw new Exception("Is not a image");
            _oldWidth = _items[_position].Image?.Width ?? throw new Exception("Is not a image");

        }

        protected override void DoExecute()
        {
            AssertImage(_items[_position]);
            _items[_position].Image?.Resize(_newWidth, _newHeight);
        }

        protected override void DoUnexecute()
        {
            _items[_position].Image?.Resize(_oldWidth, _oldHeight);
        }
    }
}

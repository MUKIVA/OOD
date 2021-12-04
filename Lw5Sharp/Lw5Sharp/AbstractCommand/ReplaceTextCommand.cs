using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Assertion;

namespace Document
{
    public class ReplaceTextCommand : CAbstractCommand
    {
        private readonly int _position;
        private readonly List<CDocumentItem> _items;
        private readonly string _newText;
        private readonly string _oldText;

        private static void AssertParagraph(CDocumentItem item)
        {
            if (item.Paragraph == null)
                throw new ArgumentException("Item isn't a paragraph");
        }

        public ReplaceTextCommand(List<CDocumentItem> items, int position, string newText, string oldText)
        {
            _items = items;
            _newText = newText;
            _position = position;
            _oldText = oldText;

            Assert.AssertionPosition(position, _items.Count);
            AssertParagraph(_items[_position]);
        }

        

        protected override void DoExecute()
        {
            AssertParagraph(_items[_position]); 

            _items[_position].Paragraph.Text = _newText; 

        }

        protected override void DoUnexecute()
        {
            AssertParagraph(_items[_position]);
            _items[_position].Paragraph.Text = _oldText;
        }
    }
}

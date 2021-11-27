using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CDocumentItem
    {
        public IImage? Image { get; }
        public IParagraph? Paragraph { get; }

        public CDocumentItem(IImage image)
        {
            Image = image;
            Paragraph = null;
        }

        public CDocumentItem(IParagraph paragraph)
        {
            Paragraph = paragraph;
            Image = null;
        }

        public string GetItemInfo()
        {
            if (Image != null)
                return $"Image: {Image.Width} {Image.Height} {Image.Path}";

            if (Paragraph != null)
                return $"Paragraph: {Paragraph.Text}";

            return string.Empty;
        }
    }
}

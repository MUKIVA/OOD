using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CDocumentResizeImage : CAbstractCommand
    {
        private int _newWidth;
        private int _newHeight;
        private int _oldWidth;
        private int _oldHeight;
        private IImage _image;

        public CDocumentResizeImage(IImage image, int width, int height)
        {
            _image = image;
            _newHeight = height;
            _newWidth = width;
            _oldHeight = image.Height;
            _oldWidth = image.Width;
        }

        protected override void DoExecute()
        {
            _image.Resize(_newWidth, _newHeight);
        }

        protected override void DoUnexecute()
        {
            _image.Resize(_oldWidth, _oldHeight);
        }
    }
}

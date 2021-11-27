using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CImage : IImage
    {

        public CImage(string path, string documentPath ,int width, int height)
        {
            RefPath = path;
            Height = height;
            Width = width;
            DocumentPath = documentPath;
        }

        public string RefPath { get; protected set; }

        public int Width { get; protected set; }

        public int Height { get; protected set; }

        public string DocumentPath { get; protected set; }

        public void Resize(int width, int height)
        {
            Width = width;
            Height = height;
        }
    }
}

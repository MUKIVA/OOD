using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CImage : IImage
    {

        public CImage(string path, int width, int height)
        {
            Path = path;
            Height = height;
            Width = width;
        }

        public string Path { get; protected set; }

        public int Width { get; protected set; }

        public int Height { get; protected set; }

        public void Resize(int width, int height)
        {
            Width = width;
            Height = height;
        }
    }
}

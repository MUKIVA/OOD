using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    public interface IImage
    {
        string RefPath { get; }
        string DocumentPath{ get; }
        int Width { get; }
        int Height { get; }
        void Resize(int width, int height);
    }
}

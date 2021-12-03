using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal interface ICommadBuildStrategy
    {
        CAbstractCommand BuildCommand(IDocument document, string[]? args);
    }
}

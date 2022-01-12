using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lw9.ViewModel
{
    public interface ISelectField
    {
        public object? GetSelectObject();
        public void SelectObject(object? obj);
        public void ResetSelect();
    }
}

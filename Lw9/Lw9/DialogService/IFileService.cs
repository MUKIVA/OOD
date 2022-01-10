using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;
using Lw9.Model;


namespace Lw9.DialogService
{
    public interface IFileService
    {
        public List<ShapeModel> Open(string filePath);
        public void Save(string filePath, List<ShapeModel> canvasData);
        
    }
}

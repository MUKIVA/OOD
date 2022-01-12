using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.ObjectModel;
using Lw9.Model;
using Lw9.ViewModel;


namespace Lw9.DialogService
{
    public interface IFileService<T>
    {
        public List<T> OpenCollection(string filePath);
        public void SaveCollection(string filePath, List<T> data);
        
    }
}

using System.Collections.Generic;


namespace Lw9.DialogService
{
    public interface IFileServiceCollection<T>
    {
        public List<T> OpenCollection(string filePath);
        public void SaveCollection(string filePath, List<T> data);
        
    }

    public interface IFileServiceObj<T>
    {
        public T Open(string filePath);
        public void Save(string filePath, T data);
        
    }
}

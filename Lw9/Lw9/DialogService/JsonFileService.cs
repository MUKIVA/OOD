using Lw9.Model;
using Lw9.ViewModel;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization.Json;
using System.IO;

namespace Lw9.DialogService
{
    public class JsonFileService : IFileService<ShapeModel>
    {
        public List<ShapeModel> OpenCollection(string filePath)
        {
            List<ShapeModel>? shapes = new();
            DataContractJsonSerializer jsonFormatter =
                new DataContractJsonSerializer(typeof(List<ShapeModel>));
            using (FileStream fs = new FileStream(filePath, FileMode.OpenOrCreate))
            {
                shapes = jsonFormatter.ReadObject(fs) as List<ShapeModel>;
            }

            return shapes!;
        }

        public void SaveCollection(string filePath, List<ShapeModel> data)
        {
            DataContractJsonSerializer jsonFormater = new DataContractJsonSerializer(typeof(List<ShapeModel>));
            using (FileStream fs = new FileStream(filePath, FileMode.Create))
            {
                jsonFormater.WriteObject(fs, data);
            }
        }
    }
}

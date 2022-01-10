using Lw9.Model;
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
    public class JsonFileService : IFileService
    {
        public List<ShapeModel> Open(string filePath)
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

        public void Save(string filePath, List<ShapeModel> canvasData)
        {
            DataContractJsonSerializer jsonFormater = new DataContractJsonSerializer(typeof(List<ShapeModel>));
            using (FileStream fs = new FileStream(filePath, FileMode.Create))
            {
                jsonFormater.WriteObject(fs, canvasData);
            }
        }
    }
}

using Lw9.Model;
using System.Collections.Generic;
using System.Runtime.Serialization.Json;
using System.IO;

namespace Lw9.DialogService
{
    public class JsonFileService : IFileServiceObj<CanvasModel>
    {
        public CanvasModel Open(string filePath)
        {
            CanvasModel? canvas = null;
            DataContractJsonSerializer jsonFormatter =
                new DataContractJsonSerializer(typeof(CanvasModel));
            using (FileStream fs = new FileStream(filePath, FileMode.OpenOrCreate))
            {
                canvas = jsonFormatter.ReadObject(fs) as CanvasModel;
            }

            return canvas!;
        }

        public void Save(string filePath, CanvasModel data)
        {
            DataContractJsonSerializer jsonFormater = new DataContractJsonSerializer(typeof(CanvasModel));
            using (FileStream fs = new FileStream(filePath, FileMode.Create))
            {
                jsonFormater.WriteObject(fs, data);
            }
        }
    }
}

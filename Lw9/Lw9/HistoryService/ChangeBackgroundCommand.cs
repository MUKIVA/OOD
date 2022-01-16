using System;
using Lw9.Model;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Lw9.HistoryService
{
    public class ChangeBackgroundCommand : IUnduableCommand, IDisposable
    {
        private CanvasModel _canvasModel;
        private string? _oldPicturePath;
        private string? _newPicturePath;
        private bool DoDeleteOnDestruct;

        public ChangeBackgroundCommand(CanvasModel canvas, string? newPicturePath, bool DoDelete = true)
        {
            _canvasModel = canvas;
            _oldPicturePath = canvas.PicturePath;
            _newPicturePath = newPicturePath;
        }

        public void Dispose()
        {
            if (File.Exists(Environment.CurrentDirectory + _newPicturePath) && DoDeleteOnDestruct)
                File.Delete(Environment.CurrentDirectory + _newPicturePath);
        }

        ~ChangeBackgroundCommand()
        {
            Dispose();
        }

        public void Execute()
        {
            _canvasModel.PicturePath = _newPicturePath;
        }

        public void Unexecute()
        {
            _canvasModel.PicturePath = _oldPicturePath;
        }
    }
}

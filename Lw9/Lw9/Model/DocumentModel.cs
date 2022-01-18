using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lw9.HistoryService;

namespace Lw9.Model
{
    public class DocumentModel
    {
        private History _history;
        private CanvasModel _canvasModel;

        public DocumentModel(History history, CanvasModel canvas)
        {
            _history = history;
            _canvasModel = canvas;
        }

        public History History
        {
            get => _history;
        }

        public CanvasModel CanvasModel
        {
            get => _canvasModel;
        }
    }
}

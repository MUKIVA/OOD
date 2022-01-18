using System.Collections.Generic;
using System.Windows.Input;
using System;

namespace Lw9.HistoryService
{

    public class History
    {

        static Stack<IUnduableCommand> undoHistory
            = new Stack<IUnduableCommand>();

        static Stack<IUnduableCommand> redoHistory
            = new Stack<IUnduableCommand>();

        public bool CanUndo() => undoHistory.Count > 0;
        public bool CanRedo() => redoHistory.Count > 0;

        public void Undo()
        {
            if (undoHistory.Count == 0) return;
            var undo = undoHistory.Pop();
            undo.Unexecute();
            redoHistory.Push(undo);
        }

        public void Redo()
        {
            if (redoHistory.Count == 0) return;
            var redo = redoHistory.Pop();
            redo.Execute();
            undoHistory.Push(redo);
        }

        public void AddToHistory(IUnduableCommand command)
        {
            redoHistory.Clear();
            GC.Collect();
            command.Execute();
            undoHistory.Push(command);
        }

        public void ClearHistory()
        {
            redoHistory.Clear();
            undoHistory.Clear();
            GC.Collect();
        }
    }
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Lw9.HistoryService
{

    public class History
    {

        static Stack<IUnduableCommand> undoHistory
            = new Stack<IUnduableCommand>();

        static Stack<IUnduableCommand> redoHistory
            = new Stack<IUnduableCommand>();

        static void Undo()
        {
            if (undoHistory.Count == 0) return;
            var undo = undoHistory.Pop();
            undo.Unexecute();
            redoHistory.Push(undo);
        }

        static void Redo()
        {
            if (redoHistory.Count == 0) return;
            var redo = redoHistory.Pop();
            redo.Execute();
            undoHistory.Push(redo);
        }

        public void AddToHistory(IUnduableCommand command)
        {
            redoHistory.Clear();
            command.Execute();
            undoHistory.Push(command);
        }

        public void ClearHistory()
        {
            redoHistory.Clear();
            undoHistory.Clear();
        }

        private ICommand? _undoCommand;
        private ICommand? _redoCommand;

        // Команды, которые можно выставлять в GUI
        public ICommand? UndoCommand
        {
            get => _undoCommand ?? (_undoCommand = new DelegateCommand(_ => 
            {
                Undo();
            }, _ => undoHistory.Count > 0 ));
        }
        public ICommand? RedoCommand
        {
            get => _redoCommand ?? (_redoCommand = new DelegateCommand(_ =>
            {
                Redo();
            }, _ => redoHistory.Count > 0));
        }
    }
}

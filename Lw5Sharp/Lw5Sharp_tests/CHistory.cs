using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CHistory
    {
        const int MAX_HISTORY_LENGTH = 10;
        const int MIN_HISTORY_LENGTH = 0;

        private int _currentCommandIndex = 0;
        private List<CAbstractCommand> _commands = new List<CAbstractCommand>(1);

        public bool CanUndo() => _currentCommandIndex > 0;
        public bool CanRedo() => _currentCommandIndex < _commands.Count;

        public void Undo()
        {
            if (CanUndo())
            {
                _commands[_currentCommandIndex - 1].Unexecute();
                --_currentCommandIndex;
            }
        }

        public void Redo()
        {
            if (CanRedo())
            {
                _commands[_currentCommandIndex].Execute();
                ++_currentCommandIndex;
            }
        }

        public void AddAndExecuteCommand(CAbstractCommand command)
        {
            if (_currentCommandIndex < _commands.Count)
            {
                _commands.RemoveRange(_currentCommandIndex, _commands.Count - _currentCommandIndex);
            }

            if (_commands.Count == MAX_HISTORY_LENGTH)
                _commands.RemoveAt(MIN_HISTORY_LENGTH);

            _commands.Add(command);
            if (_currentCommandIndex < MAX_HISTORY_LENGTH) ++_currentCommandIndex;
            _commands.Last().Execute();
        }
    }
}

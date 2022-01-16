
namespace Lw9.HistoryService
{
    public interface IUnduableCommand
    {
        public void Execute();
        public void Unexecute();
    }
}

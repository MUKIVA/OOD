
namespace Lw9.ViewModel
{
    public interface ISelectField
    {
        public object? GetSelectObject();
        public void SelectObject(object? obj);
        public void ResetSelect();
    }
}

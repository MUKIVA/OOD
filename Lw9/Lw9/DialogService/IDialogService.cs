namespace Lw9.DialogService
{
    public interface IDialogService
    {
        void ShowMessage(string message);   // показ сообщения
        string FilePath { get; set; }   // путь к выбранному файлу
        string FileName { get; set; }
        bool OpenFileDialog(string filter);  // открытие файла
        bool SaveFileDialog();  // сохранение файла
    }
}

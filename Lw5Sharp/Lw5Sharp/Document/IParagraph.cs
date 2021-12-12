
namespace Document
{
    public interface IParagraph
    {
        string Text { get; set; }
        void ReplaceText(string text);
    }
}

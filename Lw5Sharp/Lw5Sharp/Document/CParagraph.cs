
namespace Document
{
    public class CParagraph : IParagraph
    {

        public CParagraph(string text)
        {
            Text = text;
        }

        public string Text { get; set; }

        public void ReplaceText(string text)
        {
            Text = text.Trim();
        }
    }
}

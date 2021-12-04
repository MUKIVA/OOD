
namespace Document
{
    public class CParagraph : IParagraph
    {

        public CParagraph(string text)
        {
            Text = text;
        }

        public string Text { get; set; }
    }
}

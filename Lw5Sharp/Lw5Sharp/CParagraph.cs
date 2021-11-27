
namespace Document
{
    internal class CParagraph : IParagraph
    {

        public CParagraph(string text)
        {
            Text = text;
        }

        public string Text { get; set; }
    }
}

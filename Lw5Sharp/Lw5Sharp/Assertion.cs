using Document;

namespace Assertion
{
    public static class Assert
    {
        public static void AssertionPath(string path)
        {
            if (!File.Exists(path))
                throw new ArgumentException("File is not exists");
        }

        public static void AssertionPosition(int pos, int itemCount)
        {
            if (pos > itemCount || pos < 0)
                throw new IndexOutOfRangeException("Index out of range");
        }

    }
}

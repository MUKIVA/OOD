using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Document
{
    internal class CSetTitleStrategy : ICommadBuildStrategy
    {
        public CAbstractCommand BuildCommand(IDocument document, string[]? args)
        {
            if (args == null)
                throw new NullReferenceException("Ivalid args");

            if (args.Count() != 1)
                throw new ArgumentException("Invalid arguments count");

            CAbstractCommand command = new CDocumentSetTitleCommand(document, document.Title, args[0]);

            return command;
        }
    }

    internal class CInsertParagraphStrategy : ICommadBuildStrategy
    {
        public CAbstractCommand BuildCommand(IDocument document, string[]? args)
        {
            if (args == null)
                throw new NullReferenceException("Ivalid args");

            if (args.Count() != 2)
                throw new ArgumentException("Invalid arguments count");

            int parsedPosition;

            if (!int.TryParse(args[0], out parsedPosition) && args[0] != "end")
                throw new ArgumentException("Failed parse to a position");

            CAbstractCommand command = new CDocumentInsertParagraphCommand(document, args[1], (args[0] == "end") ? null : parsedPosition);

            return command;
        }
    }

    internal class CInsertImageStrategy : ICommadBuildStrategy
    {
        public CAbstractCommand BuildCommand(IDocument document, string[]? args)
        {
            if (args == null)
                throw new NullReferenceException("Ivalid args");

            if (args.Count() != 4)
                throw new ArgumentException("Invalid arguments count");

            int parsedPosition;
            int width;
            int height;

            if (!int.TryParse(args[0], out parsedPosition) && args[0] != "end")
                throw new ArgumentException("Failed parse to a position");

            if (!int.TryParse(args[1], out width) || !int.TryParse(args[2], out height))
                throw new ArgumentException("Failed parse to a image resolution");

            CAbstractCommand command = new CDocumentInsertImageCommand(
                document,
                (args[0] == "end") ? null : parsedPosition,
                width,
                height,
                args[3]
            );

            return command;
        }
    }

    internal class CReplaceTextStrategy : ICommadBuildStrategy
    {
        public CAbstractCommand BuildCommand(IDocument document, string[]? args)
        {
            if (args == null)
                throw new NullReferenceException("Ivalid args");

            if (args.Count() != 2)
                throw new ArgumentException("Invalid arguments count");

            int position;

            if (!int.TryParse(args[0], out position))
                throw new ArgumentException("Invalid position for replace");

            CDocumentItem item = document.GetItem(position);

            if (item.Paragraph == null)
                throw new Exception("Item is not a paragraph");

            CAbstractCommand command = new CDocumentReplaceTextCommand(item.Paragraph, args[1]);

            return command;
        }
    }

    internal class CResizeImageStrategy : ICommadBuildStrategy
    {
        public CAbstractCommand BuildCommand(IDocument document, string[]? args)
        {
            if (args == null)
                throw new NullReferenceException("Ivalid args");

            if (args.Count() != 3)
                throw new ArgumentException("Invalid arguments count");

            int position;
            int width;
            int height;

            if (!int.TryParse(args[0], out position))
                throw new ArgumentException("Invalid position for resize");

            if (!int.TryParse(args[1], out width) || !int.TryParse(args[2], out height))
                throw new ArgumentException("Ivalid height or width value");

            CDocumentItem item = document.GetItem(position);

            if (item.Image == null)
                throw new Exception("Item is not a image");

            CAbstractCommand command = new CDocumentResizeImage(item.Image, width, height);

            return command;
        }
    }

    internal class CDeleteItemStrategy : ICommadBuildStrategy
    {
        public CAbstractCommand BuildCommand(IDocument document, string[]? args)
        {
            if (args == null)
                throw new NullReferenceException("Ivalid args");

            if (args.Count() != 1)
                throw new ArgumentException("Invalid arguments count");

            int position;

            if (!int.TryParse(args[0], out position))
                throw new ArgumentException("Invalid position for resize");

            CAbstractCommand command = new CDocumentDeleteItemCommand(document, position);

            return command;
        }
    }
}

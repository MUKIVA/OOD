// See https://aka.ms/new-console-template for more information
using Document;

CMenu m = new CMenu(Console.In, Console.Out);
CDocument d = new CDocument();

m.AddItem("help", "Show all instructions", new CHelpCommand(m));
m.AddItem("exit", "Exit from programm", new CExitCommand(m));
m.AddItem("title", "Set new title for document\t<newTitle>", new CSetTitleCommand(d));
m.AddItem("list", "Show info about document", new CListCommand(d, Console.Out));
m.AddItem("undo", "Cancels the last action", new CUndoCommand(d));
m.AddItem("redo", "Restores the canceled action", new CRedoCommand(d));
m.AddItem("ip", "Inserts a paragraph in the appropriate position\t<position>|end <text>", new CInsertParagraphCommand(d));
m.AddItem("ii", "Inserts a image in the appropriate position\t<position>|end <width> <height> <path>", new CInsertImageCommand(d));
m.AddItem("rpt", "Replace paragraph text\t<position> <newText>", new CReplaceTextCommand(d));
m.AddItem("ris", "Resize image\t<position> <newWidth> <newHeight>", new CResizeImageCommand(d));
m.AddItem("del", "Delete item from position\t<position>", new CDeleteItemCommand(d));
m.AddItem("save", "Save html document\t<FilePath>", new CSaveCommand(d));
m.Run();
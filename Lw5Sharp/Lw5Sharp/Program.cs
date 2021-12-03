// See https://aka.ms/new-console-template for more information
using Document;


CMenu m = new CMenu(Console.In, Console.Out);
CDocument d = new CDocument();

m.AddItem("help", "Show all instructions",                                                                   m.ShowInstructions);
m.AddItem("exit", "Exit from programm",                                                                      m.Exit);
m.AddItem("title", "Set new title for document                      <newTitle>",                             (_1) => m.SetTitle(d, _1));
m.AddItem("list", "Show info about document",                                                                (_1) => m.ShowList(d, _1));
m.AddItem("undo", "Cancels the last action",                                                                 (_1) => m.Undo(d, _1));
m.AddItem("redo", "Restores the canceled action",                                                            (_1) => m.Redo(d, _1));
m.AddItem("ip", "Inserts a paragraph in the appropriate position    <position>|end <text>",                  (_1) => m.InsertParagraph(d, _1));
m.AddItem("ii", "Inserts a image in the appropriate position        <position>|end <width> <height> <path>", (_1) => m.InsertImage(d, _1));
m.AddItem("rpt", "Replace paragraph text                            <position> <newText>",                   (_1) => m.ReplaceText(d, _1));
m.AddItem("ris", "Resize image                                      <position> <newWidth> <newHeight>",      (_1) => m.ResizeImage(d, _1));
m.AddItem("del", "Delete item from position                         <position>",                             (_1) => m.DeleteItem(d, _1));
m.AddItem("save", "Save html document                               <FilePath>",                             (_1) => m.SaveDocument(d, _1));
m.Run();
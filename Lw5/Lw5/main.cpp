#include <string>
#include <iostream>
#include <memory>
#include <filesystem>
#include <optional>
#include "CHtmlDocument.h"
#include "CSetTitleCommand.h"
#include "CInsertImageCommand.h"
#include "CInsertParagraphCommand.h"
#include "CReplaceTextCommand.h"
#include "CResizeImageCommand.h"
#include "CDeleteItemCommand.h"
#include "CMenuHelpCommand.h"
#include "CExitMenuCommand.h"
#include "CMenu.h"

class CEditor
{
public:
	CEditor(
		std::istream& in,
		std::ostream& out,
		std::unique_ptr<IDocument> document = std::make_unique<CHtmlDocument>())
		: m_menu(in, out)
		, m_document(move(document))
		, m_in(in)
		, m_out(out)
	{
		m_menu.AddItem("help", "Show instructions", std::bind(&CMenu::ShowInstructions, &m_menu));
		m_menu.AddItem("exit", "Exit from this menu", std::bind(&CMenu::Exit, &m_menu));
		AddMenuItem("title", "Change title.\t<new title>", (MenuHandler)&CEditor::SetTitleCommand);
		AddMenuItem("list", "Show all elements of document", (MenuHandler)&CEditor::ListCommand);
		AddMenuItem("ip", "Insert paragraph into given position.\tend|<pos> <text>", (MenuHandler)&CEditor::InsertParagraphCommand);
		AddMenuItem("ii", "Insert image into given position.\tend|<pos> <width> <height> <Path>", (MenuHandler)&CEditor::InsertImageCommand);	
		AddMenuItem("rpt", "Replace paragraph text.\t<index> <new text>", (MenuHandler)&CEditor::ReplaceTextCommand);
		AddMenuItem("rsi", "Resize image.\t<index> <new width> <new height>", (MenuHandler)&CEditor::ResizeImageCommand);
		AddMenuItem("del", "Delete item from document.\t<index>", (MenuHandler)&CEditor::DeleteItemCommand);
		AddMenuItem("undo", "Cancel action", (MenuHandler)&CEditor::UndoCommand);
		AddMenuItem("redo", "Returning an action", (MenuHandler)&CEditor::RedoCommand);
		AddMenuItem("save", "Save html document", (MenuHandler)&CEditor::SaveCommand);
	}


	void Start()
	{
		m_menu.ShowInstructions();
		m_menu.Run();
	}

private:
	typedef void (CEditor::*MenuHandler)(std::istream&); 

	void AddMenuItem(const std::string& shortcut, const std::string& description, MenuHandler handler)
	{
		m_menu.AddItem(shortcut, description, std::bind(handler, this, std::placeholders::_1));
	}

	void SetTitleCommand(std::istream& args)
	{
		std::string newTitle;
		if (!std::getline(args, newTitle))
			throw std::invalid_argument("Invalid set title argument");
		
		m_document->HandleCommand(std::make_unique<CSetTitleCommand>(*m_document, newTitle));
	}

	void ListCommand(std::istream&)
	{
		m_document->ShowItems(m_out);
	}

	void InsertParagraphCommand(std::istream& args)
	{
		std::string pos;
		std::string text;
		if (!(args >> pos))
			throw std::invalid_argument("Invalid pos argument paragraph");

		if (!std::getline(args, text))
			throw std::invalid_argument("Invalid text argument paragraph");

		if (pos == "end")
		{
			m_document->HandleCommand(std::make_unique<CInsertParagraphCommand>(*m_document, text, std::nullopt));
		}
		else
		{
			try
			{
				m_document->HandleCommand(std::make_unique<CInsertParagraphCommand>(*m_document, text, std::stoull(pos)));
			}
			catch (const std::exception&)
			{
				throw std::invalid_argument("Invalid pos argument paragraph");
			}
		}
	}

	void InsertImageCommand(std::istream& args)
	{
		std::string pos;
		std::string width;
		std::string height;
		Path path;
		
		if (!(args >> pos))
			throw std::invalid_argument("Invalid pos argument");

		if (!(args >> width))
			throw std::invalid_argument("Invalid width argument");

		if (!(args >> height))
			throw std::invalid_argument("Invalid height argument");

		if (!(args >> path))
			throw std::invalid_argument("Invalid path argument");

		try
		{
			if (pos == "end")
			{
				m_document->HandleCommand(std::make_unique<CInsertImageCommand>
				(
					*m_document,
					path, std::stoi(width),
					std::stoi(height),
					std::nullopt
				));
			}
			else
			{
				m_document->HandleCommand(std::make_unique<CInsertImageCommand>
				(
					*m_document,
					path, std::stoi(width),
					std::stoi(height),
					std::stoull(pos)
				));
			}
		}
		catch (const std::exception&)
		{
			throw std::invalid_argument("Invalid pos argument");
		}
	}

	void ReplaceTextCommand(std::istream& args)
	{
		std::string pos;
		std::string text;
		if (!(args >> pos))
			throw std::invalid_argument("Invalid pos argument paragraph");

		if (!std::getline(args, text))
			throw std::invalid_argument("Invalid text argument paragraph");
		
		CDocumentItem item = m_document->GetItem(std::stoull(pos));
		if (item.GetParagraph() == nullptr)
			throw std::invalid_argument("The index number does not match the paragraph");

		item.GetParagraph()->SetText(text);
	}

	void ResizeImageCommand(std::istream& args)
	{
		std::string pos;
		int w, h;
		if (!(args >> pos))
			throw std::invalid_argument("Invalid pos argument");

		if (!(args >> w >> h))
			throw std::invalid_argument("Invalid width or height argument");

		CDocumentItem item = m_document->GetItem(std::stoull(pos));
		if (item.GetImage() == nullptr)
			throw std::invalid_argument("The index number does not match the image");

		item.GetImage()->Resize(w, h);
	}

	void DeleteItemCommand(std::istream& args)
	{
		size_t index;
		
		if (!(args >> index))
			throw std::invalid_argument("Invalide index");

		m_document->HandleCommand(std::make_unique<CDeleteItemCommand>(*m_document, index));
	}

	void UndoCommand(std::istream&)
	{
		m_document->Undo();
	}

	void RedoCommand(std::istream&)
	{
		m_document->Redo();
	}

	void SaveCommand(std::istream& args)
	{
		Path path;
		if (!(args >> path))
			throw std::invalid_argument("Invalid path argument");

		m_document->Save(path);
	}

	CMenu m_menu;
	std::unique_ptr<IDocument> m_document;
	std::istream& m_in;
	std::ostream& m_out;
};


int main()
{
	CEditor editor(std::cin, std::cout);
	editor.Start();
}

//#include <iostream>
//#include <memory>
//#include "CEditor.h"
//
//
//#include <iostream>
//#include <memory>
//#include "CMenu.h"
//#include "CHtmlDocument.h"
//#include "CSetTitleCommand.h"
//#include "CInsertImageCommand.h"
//#include "CInsertParagraphCommand.h"
//#include "CReplaceTextCommand.h"
//#include "CResizeImageCommand.h"
//#include "CDeleteItemCommand.h"
//#include "CMenuHelpCommand.h"
//#include "CExitMenuCommand.h"

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
#include "CMenu.h"



namespace
{
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
			AddMenuItem("title", "Change title.\t<new title>", &CEditor::BuildSetTitleCommand);
		}

		void Start()
		{
			m_menu.ShowInstructions();
			m_menu.Run();
		}

	private:
		typedef void (CEditor::*MenuHandler)(std::istream& args);
		//typedef std::function<void(std::istream&)> MenuHandler; 

		void AddMenuItem(const std::string& shortcut, const std::string& description, MenuHandler handler)
		{
			m_menu.AddItem(shortcut, description, std::bind(handler, this, m_in));
		}

		void BuildSetTitleCommand(std::ifstream& args)
		{
			return;
		}

		CMenu m_menu;
		std::unique_ptr<IDocument> m_document;
		std::istream& m_in;
		std::ostream& m_out;
	};
}


int main()
{
	CEditor editor(std::cin, std::cout);
	editor.Start();
}
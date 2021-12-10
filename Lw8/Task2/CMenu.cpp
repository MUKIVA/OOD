#include "CMenu.h"

CMenu::CMenu(std::istream& in, std::ostream& out)
	: m_in(in)
	, m_out(out)
{
}

void CMenu::AddItem(const std::string& shortcut, const std::string& description, const Command& command)
{
	m_items.emplace_back(Item(shortcut, description, command));
}

void CMenu::Run()
{
	ShowInstructions();
	std::string command;
	while ((m_out << ">")
		&& m_in >> command
		&& ExecuteCommand(command))
	{
	}
}

void CMenu::ShowInstructions() const
{
	m_out << "Command list:\n";
	for (const auto& item : m_items)
	{
		m_out << "\t" << item.shortcut << ":\t" << item.description << "\n";
	}
}

void CMenu::Exit()
{
	m_exit = true;
}

bool CMenu::ExecuteCommand(const std::string& command)
{
	m_exit = false;

	auto it = std::find_if(m_items.begin(), m_items.end(), [&](const Item& item) {
		return item.shortcut == command;
	});

	if (it != m_items.end())
	{
		try
		{
			it->command();
		}
		catch (const std::exception& e)
		{
			m_out << e.what() << std::endl;
		}
	}
	else
	{
		m_out << "Uncknown command\n";
	}
	return !m_exit;
}

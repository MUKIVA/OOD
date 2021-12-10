#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <vector>

class CMenu
{

public:

	typedef std::function<void()> Command;

	CMenu(std::istream& in, std::ostream& out);

	void AddItem(const std::string& shortcut, const std::string& description, const Command& command);

	void Run();

	void ShowInstructions() const;

	void Exit();

private:

	struct Item
	{
		Item(const std::string& shortcut, const std::string& description, const Command& command)
			: shortcut(shortcut)
			, description(description)
			, command(command)
		{

		}

		std::string shortcut;
		std::string description;
		Command command;
	};

	bool ExecuteCommand(const std::string& command);
	


	std::istream& m_in;
	std::ostream& m_out;
	bool m_exit = false;
	std::vector<Item> m_items;
};


#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include "ICommand.h"


class CMenu
{
public:
	typedef std::function<void()> Command;

	CMenu(std::istream& is, std::ostream& os)
		: m_in(is)
		, m_out(os)
	{
	}

	/*void AddItem(const std::string& shortcut, const std::string& description, std::unique_ptr<ICommand>&& command)
	{
		m_items.emplace_back(shortcut, description, move(command));
	}*/


	void AddItem(const std::string& shortcut, const std::string& description, const Command& command)
	{
		m_items.emplace_back(shortcut, description, command);
	}

	void Run()
	{
		std::string command;
		while ((m_out << ">") 
			&& std::getline(m_in, command) 
			&& ExecuteCommand(command))
		{
		}
	}

	void ShowInstructions() const
	{
		m_out << "Command list:\n";
		for (auto& item : m_items)
		{
			m_out << "\t" << item.shortcut << ":" << item.description << "\n";
		}
	}

	void Exit()
	{
		m_exit = true;
	}

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

	bool ExecuteCommand(const std::string& command)
	{
		m_exit = false;
		auto it = std::find_if(m_items.begin(), m_items.end(), [&](const Item& item) 
		{
			return item.shortcut == command;
		});
		if (it != m_items.end())
			it->command();
		else
			m_out << "Uncnown command\n";

		return !m_exit;
	}

	std::istream& m_in;
	std::ostream& m_out;
	std::vector<Item> m_items;
	bool m_exit = false;
};
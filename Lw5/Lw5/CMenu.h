#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <sstream>
#include "ICommand.h"


class CMenu
{
public:
	typedef std::function<void(std::istream& args)> Command;
	//typedef std::function<std::unique_ptr<ICommand>(std::istream&)> CommandBuilder;

	CMenu(std::istream& is, std::ostream& os)
		: m_in(is)
		, m_out(os)
	{
	}

	void AddItem(const std::string& shortcut, const std::string& description, const Command& command)
	{
		m_items.emplace_back(shortcut, description, command);
	}

	/*void AddItem(const std::string& shortcut, const std::string& description, std::unique_ptr<ICommand> command)
	{
		m_items.emplace_back(shortcut, description, move(command));
	}*/

	/*void AddItem(const std::string& shortcut, const std::string& description, CommandBuilder commandBuilder)
	{
		m_items.emplace_back(shortcut, description, commandBuilder(m_in));
	}*/

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

	bool ExecuteCommand(const std::string& args)
	{
		std::istringstream iss(args);

		std::string command;
		iss >> command;

		m_exit = false;
		auto it = std::find_if(m_items.begin(), m_items.end(), [&](const Item& item) {
			return item.shortcut == command;
		});
		if (it != m_items.end())
			try
			{
				it->command(iss);
			}
			catch (const std::exception& e)
			{
				m_out << e.what() << std::endl;
			}
		else
			m_out << "Uncknown command\n";

		return !m_exit;
	}

	std::vector<Item> m_items;
	bool m_exit = false;
	std::istream& m_in;
	std::ostream& m_out;
};
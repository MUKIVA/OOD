#pragma once

#include <memory>
#include <vector>
#include "ICommand.h"

class CHistory
{
public:
	bool CanUndo() const
	{
		return m_currentCommandIndex != 0;
	}

	bool CanRedo() const
	{
		return m_currentCommandIndex != m_commands.size();
	}

	void Undo()
	{
		if (CanUndo())
		{
			m_commands[m_currentCommandIndex - 1]->Unexecute();
			--m_currentCommandIndex;
		}
	}

	void Redo()
	{
		if (CanRedo())
		{
			m_commands[m_currentCommandIndex]->Execute();
			++m_currentCommandIndex;
		}
	}
	void AddAndExecuteCommand(std::unique_ptr<ICommand>&& command)
	{
		if (m_currentCommandIndex < m_commands.size())
		{
			m_commands.resize(m_currentCommandIndex);
		}

		m_commands.push_back(move(command));
		m_commands.back()->Execute();
		++m_currentCommandIndex;
	}

private:
	std::vector<std::unique_ptr<ICommand>> m_commands;
	unsigned int m_currentCommandIndex = 0;
};
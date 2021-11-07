#pragma once
#include "ICommand.h"
#include "CMenu.h"


class CMenuHelpCommand : public ICommand
{
public:
	CMenuHelpCommand(const CMenu& menu)
		: m_menu(menu) 
	{
	}

	void Execute() override
	{
		m_menu.ShowInstructions();
	}

	void Unexecute() override
	{
	}

private:
	const CMenu& m_menu;
};
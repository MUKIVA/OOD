#pragma once

#include "CMenu.h"
#include "ICommand.h"

class CExitMenuCommand : public ICommand
{
public:
	CExitMenuCommand(CMenu& menu)
		: m_menu(menu)
	{

	}

	void Execute() override
	{
		m_menu.Exit();
	}

	void Unexecute() override
	{
		
	}

private:
	CMenu& m_menu;

};
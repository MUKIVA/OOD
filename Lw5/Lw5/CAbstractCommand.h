#pragma once
#include "ICommand.h"

class CAbstractCommand : public ICommand
{
public:
	void Execute() final
	{
		DoExecute();
		m_executed = true;
	}
	void Unexecute() final
	{
		DoUnexecute();
		m_executed = false;
	}

protected:
	virtual void DoExecute() = 0;
	virtual void DoUnexecute() = 0;


private:
	bool m_executed = false;
};
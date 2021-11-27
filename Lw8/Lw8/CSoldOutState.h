#pragma once
#include "IGumballMachine.h"
#include "IState.h"

class CSoldOutState : public IState
{
public:
	CSoldOutState(IGumballMachine& gumballMachine, std::ostream& out);

	void InsertQuarter();
	void EjectQuarter();
	void TurnCrank();
	void Dispense();
	std::string ToString() const;

private:
	IGumballMachine& m_gumballMachine;
	std::ostream& m_out;
};

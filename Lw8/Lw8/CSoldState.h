#pragma once
#include <iostream>
#include "IState.h"
#include "IGumballMachine.h"

class CSoldState : public IState
{
public:
	CSoldState(IGumballMachine& gumballMachine, std::ostream& out);

	void InsertQuarter();
	void EjectQuarter();
	void TurnCrank();
	void Dispense();
	std::string ToString() const;

private:
	IGumballMachine& m_gumballMachine;
	std::ostream& m_out;
};

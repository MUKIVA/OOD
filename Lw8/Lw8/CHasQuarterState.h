#pragma once
#include "IState.h"
#include "IGumballMachine.h"

class CHasQuarterState : public IState
{
public:
	CHasQuarterState(IGumballMachine& gumballMachine, std::ostream& out);

	void InsertQuarter();
	void EjectQuarter();
	void TurnCrank();
	void Dispense();
	std::string ToString() const;

private:
	IGumballMachine& m_gumballMachine;
	std::ostream& m_out;

};

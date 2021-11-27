#include "CHasQuarterState.h"
#include <iostream>

CHasQuarterState::CHasQuarterState(IGumballMachine& gumballMachine, std::ostream& out = std::cout)
	: m_gumballMachine(gumballMachine)
	, m_out(out)
{
}

void CHasQuarterState::InsertQuarter()
{
	m_out << "You can't insert another quarter\n";
}

void CHasQuarterState::EjectQuarter()
{
	m_out << "Quarter returned\n";
	m_gumballMachine.SetNoQuarterState();
}

void CHasQuarterState::TurnCrank()
{
	m_out << "You turned...\n";
	m_gumballMachine.SetSoldState();
}

void CHasQuarterState::Dispense()
{
	m_out << "No gumball dispensed\n";
}

std::string CHasQuarterState::ToString() const
{
	return "waiting for turn of crank";
}


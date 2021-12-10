#include "CHasQuarterState.h"
#include <iostream>

using namespace withState;

CHasQuarterState::CHasQuarterState(IGumballMachine& gumballMachine, std::ostream& out = std::cout)
	: m_gumballMachine(gumballMachine)
	, m_out(out)
{
}

void CHasQuarterState::InsertQuarter()
{
	if (m_gumballMachine.GetQuartersAmount() == MAX_QUARTERS)
	{
		m_out << "You can't insert another quarter\n";
		return;
	}
	m_gumballMachine.IncQuarter();
	m_out << "You inserted a quarter\n";
}

void CHasQuarterState::EjectQuarter()
{
	m_out << "Quarter returned\n";
	m_gumballMachine.GiveOutCoins();
	m_gumballMachine.SetNoQuarterState();
}

void CHasQuarterState::TurnCrank()
{
	m_out << "You turned...\n";
	m_gumballMachine.DecQuarter();
	m_gumballMachine.SetSoldState();
}

void CHasQuarterState::Dispense()
{
	m_out << "No gumball dispensed\n";
}

void withState::CHasQuarterState::Refill(unsigned ballCount)
{
	m_out << "You refill gumball machine\n";
	m_gumballMachine.SetBallCount(ballCount);
}

std::string CHasQuarterState::ToString() const
{
	return "waiting for turn of crank";
}

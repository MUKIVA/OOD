#include "CSoldOutState.h"
#include <iostream>

using namespace withState;

CSoldOutState::CSoldOutState(IGumballMachine& gumballMachine, std::ostream& out = std::cout)
	: m_gumballMachine(gumballMachine)
	, m_out(out)
{
}

void CSoldOutState::InsertQuarter()
{
	m_out << "You can't insert a quarter, the machine is sold out\n";
}

void CSoldOutState::EjectQuarter()
{
	if (m_gumballMachine.GetQuartersAmount() != 0)
	{
		m_out << "Return quarters";
		m_gumballMachine.GiveOutCoins();
	}
	else
	{
		m_out << "You can't eject, you haven't inserted a quarter yet\n";
	}
}

void CSoldOutState::TurnCrank()
{
	m_out << "You turned but there's no gumballs\n";
}

void CSoldOutState::Dispense()
{
	m_out << "No gumball dispensed\n";
}

void withState::CSoldOutState::Refill(unsigned ballCount)
{
	if (ballCount == 0)
	{
		m_out << "You did nothing\n";
		return;
	}

	m_out << "You refill gumball machine\n";
	m_gumballMachine.SetBallCount(ballCount);
	if (m_gumballMachine.GetQuartersAmount() == 0)
	{
		m_gumballMachine.SetNoQuarterState();
	}
	else
	{
		m_gumballMachine.SetHasQuarterState();
	}
}

std::string CSoldOutState::ToString() const
{
	return "sold out";
}

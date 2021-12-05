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

std::string CSoldOutState::ToString() const
{
	return "sold out";
}

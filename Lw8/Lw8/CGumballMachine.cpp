#include "CGumballMachine.h"
#include <iostream>
#include <format>

CGumballMachine::CGumballMachine(unsigned numBalls, std::ostream& out)
	: m_count(numBalls)
	, m_out(out)
{
	if (m_count > 0)
	{
		SetNoQuarterState();
	}
	else
	{
		SetSoldOutState();
	}
}

void CGumballMachine::InsertQuarter()
{
	m_currentState->InsertQuarter();
}

void CGumballMachine::EjectQuarter()
{
	m_currentState->EjectQuarter();
}

void CGumballMachine::TurnCrank()
{
	m_currentState->TurnCrank();
}

void CGumballMachine::Dispense()
{
	m_currentState->Dispense();
}

std::string CGumballMachine::ToString() const
{
	std::string strw = "Mighty Gumball, Inc.\n"
					   "C++-enabled Standing Gumball Model #2016 (with state)\n"
					   "Inventory: {} gumball{}\n"
					   "Machine is {}\n";
	strw = std::format(strw, m_count, m_count != 1 ? "s" : "", m_currentState->ToString());
	return strw;
}

void CGumballMachine::ReleaseBall()
{
	if (m_count != 0)
	{
		m_out << "A gumball comes rolling out the slot...\n";
		--m_count;
	}
}

unsigned CGumballMachine::GetBallCount() const
{
	return m_count;
}

void CGumballMachine::SetSoldOutState()
{
	m_currentState = std::make_unique<CSoldOutState>(static_cast<IGumballMachine&>(*this), m_out);
}

void CGumballMachine::SetNoQuarterState()
{
	m_currentState = std::make_unique<CNoQuarterState>(static_cast<IGumballMachine&>(*this), m_out);
}

void CGumballMachine::SetSoldState()
{
	m_currentState = std::make_unique<CSoldState>(static_cast<IGumballMachine&>(*this), m_out);
}

void CGumballMachine::SetHasQuarterState()
{
	m_currentState = std::make_unique<CHasQuarterState>(static_cast<IGumballMachine&>(*this), m_out);
}

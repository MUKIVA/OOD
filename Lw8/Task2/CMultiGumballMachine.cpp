#include "CMultiGumballMachine.h"
#include "CSoldState.h"
#include "CSoldOutState.h"
#include "CNoQuarterState.h"
#include "CHasQuarterState.h"
#include "IState.h"
#include <format>

using namespace withState;

CMultiGumballMachine::CMultiGumballMachine(unsigned ballsCount, std::ostream& out)
	: m_out(out)
	, m_ballCount(ballsCount)
{
	if (m_ballCount > 0)
	{
		SetNoQuarterState();
	}
	else
	{
		SetSoldOutState();
	}
}

void withState::CMultiGumballMachine::InsertQuarter()
{
	m_currentState->InsertQuarter();
}

void withState::CMultiGumballMachine::EjectQuarter()
{
	m_currentState->EjectQuarter();
}

void withState::CMultiGumballMachine::TurnCrank()
{
	m_currentState->TurnCrank();
}

void withState::CMultiGumballMachine::Dispense()
{
	m_currentState->Dispense();
}

std::string withState::CMultiGumballMachine::ToString() const
{
	std::string strw = "Mighty Gumball, Inc.\n"
					   "C++-enabled Standing Gumball Model #2016 (with state)\n"
					   "Inventory: {} gumball{}\n"
					   "Quarters: {}\n"
					   "Machine is {}\n";
	strw = std::format(strw, m_ballCount, m_ballCount != 1 ? "s" : "", m_quarterCount, m_currentState->ToString());
	m_out << strw;
	return strw;
}

void withState::CMultiGumballMachine::Refill(unsigned ballsCount)
{
	if (dynamic_cast<CSoldState*>(m_currentState.get()) != nullptr)
	{
		m_out << "You can't fill the gumball machine when it sells the ball\n";
		return;
	}

	m_ballCount = ballsCount;
	if (m_ballCount > 0 && m_quarterCount == 0)
	{
		SetNoQuarterState();
	}
	else if (m_ballCount > 0 && m_quarterCount > 0)
	{
		SetHasQuarterState();
	}
	else
	{
		SetSoldOutState();
	}
}

void withState::CMultiGumballMachine::ReleaseBall()
{
	if (m_ballCount != 0)
	{
		m_out << "A gumball comes rolling out the slot...\n";
		--m_ballCount;
	}
}

unsigned withState::CMultiGumballMachine::GetBallCount() const
{
	return m_ballCount;
}

unsigned withState::CMultiGumballMachine::GetQuartersAmount() const
{
	return m_quarterCount;
}

void withState::CMultiGumballMachine::IncQuarter()
{
	++m_quarterCount;
}

void withState::CMultiGumballMachine::DecQuarter()
{
	--m_quarterCount;
}

void withState::CMultiGumballMachine::GiveOutCoins()
{
	m_quarterCount = 0;
}

void CMultiGumballMachine::SetSoldOutState()
{
	m_currentState.reset(new CSoldOutState(*this, m_out));
}

void CMultiGumballMachine::SetNoQuarterState()
{
	m_currentState.reset(new CNoQuarterState(*this, m_out));
}

void CMultiGumballMachine::SetSoldState()
{
	m_currentState.reset(new CSoldState(*this, m_out));
}

void CMultiGumballMachine::SetHasQuarterState()
{
	m_currentState.reset(new CHasQuarterState(*this, m_out));
}

#include "CNaiveMultiGumballMachine.h"
#include <format>

Naive::CNaiveMultiGumballMachine::CNaiveMultiGumballMachine(unsigned ballsCount, std::ostream& out)
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

void Naive::CNaiveMultiGumballMachine::InsertQuarter()
{
	switch (m_currentState)
	{
	case Naive::State::SOLD_OUT:
		m_out << "You can't insert a quarter, the machine is sold out\n";
		break;
	case Naive::State::NO_QUARTER:
		m_out << "You inserted a quarter\n";
		IncQuarter();
		SetHasQuarterState();
		break;
	case Naive::State::HAS_QUARTER:
		if (GetQuartersAmount() == MAX_QUARTERS)
		{
			m_out << "You can't insert another quarter\n";
			return;
		}
		IncQuarter();
		m_out << "You inserted a quarter\n";
		break;
	case Naive::State::SOLD:
		m_out << "Please wait, we're already giving you a gumball\n";
		break;
	}
}

void Naive::CNaiveMultiGumballMachine::EjectQuarter()
{
	switch (m_currentState)
	{
	case Naive::State::SOLD_OUT:
		if (GetQuartersAmount() != 0)
		{
			m_out << "Return quarters";
			GiveOutCoins();
		}
		else
		{
			m_out << "You can't eject, you haven't inserted a quarter yet\n";
		}
		break;
	case Naive::State::NO_QUARTER:
		m_out << "You haven't inserted a quarter\n";
		break;
	case Naive::State::HAS_QUARTER:
		m_out << "Quarter returned\n";
		GiveOutCoins();
		SetNoQuarterState();
		break;
	case Naive::State::SOLD:
		m_out << "Sorry you already turned the crank\n";
		break;
	}
}

void Naive::CNaiveMultiGumballMachine::TurnCrank()
{
	switch (m_currentState)
	{
	case Naive::State::SOLD_OUT:
		m_out << "You turned but there's no gumballs\n";
		break;
	case Naive::State::NO_QUARTER:
		m_out << "You turned but there's no quarter\n";
		break;
	case Naive::State::HAS_QUARTER:
		m_out << "You turned...\n";
		DecQuarter();
		SetSoldState();
		break;
	case Naive::State::SOLD:
		m_out << "Turning twice doesn't get you another gumball\n";
		break;
	}
}

void Naive::CNaiveMultiGumballMachine::Dispense()
{
	switch (m_currentState)
	{
	case Naive::State::SOLD_OUT:
		m_out << "No gumball dispensed\n";
		break;
	case Naive::State::NO_QUARTER:
		m_out << "You need to pay first\n";
		break;
	case Naive::State::HAS_QUARTER:
		m_out << "No gumball dispensed\n";
		break;
	case Naive::State::SOLD:
		ReleaseBall();
		if (GetBallCount() == 0)
		{
			m_out << "Oops, out of gumballs\n";
			SetSoldOutState();
		}
		else if (GetQuartersAmount() != 0)
		{
			SetHasQuarterState();
		}
		else
		{
			SetNoQuarterState();
		}
		break;
	}
}

std::string Naive::CNaiveMultiGumballMachine::ToString() const
{
	std::string state;
	switch (m_currentState)
	{
	case Naive::State::SOLD_OUT:
		state = "sold out";
		break;
	case Naive::State::NO_QUARTER:
		state = "waiting for quarter";
		break;
	case Naive::State::HAS_QUARTER:
		state = "waiting for turn of crank";
		break;
	case Naive::State::SOLD:
		state = "delivering a gumball";
		break;
	}

	std::string strw = "Mighty Gumball, Inc.\n"
					   "C++-enabled Standing Gumball Model #2016 (with state)\n"
					   "Inventory: {} gumball{}\n"
					   "Quarters: {}\n"
					   "Machine is {}\n";
	strw = std::format(strw, m_ballCount, m_ballCount != 1 ? "s" : "", m_quarterCount, state);
	return strw;
}

void Naive::CNaiveMultiGumballMachine::Refill(unsigned ballCount)
{
	if (m_currentState == State::SOLD)
	{
		m_out << "You can't fill the gumball machine when it sells the ball\n";
		return;
	}

	m_ballCount = ballCount;
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

void Naive::CNaiveMultiGumballMachine::ReleaseBall()
{
	if (m_ballCount != 0)
	{
		m_out << "A gumball comes rolling out the slot...\n";
		--m_ballCount;
	}
}

unsigned Naive::CNaiveMultiGumballMachine::GetBallCount() const
{
	return m_ballCount;
}

unsigned Naive::CNaiveMultiGumballMachine::GetQuartersAmount() const
{
	return m_quarterCount;
}

void Naive::CNaiveMultiGumballMachine::IncQuarter()
{
	++m_quarterCount;
}

void Naive::CNaiveMultiGumballMachine::DecQuarter()
{
	--m_quarterCount;
}

void Naive::CNaiveMultiGumballMachine::GiveOutCoins()
{
	m_quarterCount = 0;
}

void Naive::CNaiveMultiGumballMachine::SetSoldOutState()
{
	m_currentState = State::SOLD_OUT;
}

void Naive::CNaiveMultiGumballMachine::SetNoQuarterState()
{
	m_currentState = State::NO_QUARTER;
}

void Naive::CNaiveMultiGumballMachine::SetSoldState()
{
	m_currentState = State::SOLD;
}

void Naive::CNaiveMultiGumballMachine::SetHasQuarterState()
{
	m_currentState = State::HAS_QUARTER;
}

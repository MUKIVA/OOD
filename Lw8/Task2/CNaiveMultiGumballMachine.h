#pragma once
#include "IGumballMachine.h"
#include <iostream>

namespace Naive
{
	const unsigned MAX_QUARTERS = 5;

	enum class State
	{
		SOLD_OUT,
		NO_QUARTER,
		HAS_QUARTER,
		SOLD
	};

	class CNaiveMultiGumballMachine
	{
	public:
		CNaiveMultiGumballMachine(unsigned ballsCount, std::ostream& out);


		void InsertQuarter();
		void EjectQuarter();
		void TurnCrank();
		void Dispense();
		std::string ToString() const;
		void Refill(unsigned ballCount);

		void ReleaseBall();
		unsigned GetBallCount() const;
		unsigned GetQuartersAmount() const;
		void IncQuarter();
		void DecQuarter();
		void GiveOutCoins();

	private:
		void SetSoldOutState();
		void SetNoQuarterState();
		void SetSoldState();
		void SetHasQuarterState();

	private:
		unsigned m_ballCount = 0;
		unsigned m_quarterCount = 0;
		State m_currentState;
		std::ostream& m_out;


	};
}

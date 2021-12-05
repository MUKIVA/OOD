#pragma once
#include "IGumballMachine.h"
#include "IState.h"
#include <iostream>

namespace withState
{
	class CMultiGumballMachine : public IGumballMachine
	{
	public:

		CMultiGumballMachine(unsigned ballsCount, std::ostream& out);

		void InsertQuarter();
		void EjectQuarter();
		void TurnCrank();
		void Dispense();
		std::string ToString() const;

		void Refill(unsigned ballsCount);

		// Унаследовано через IGumballMachine
		void ReleaseBall() override;
		unsigned GetBallCount() const override;
		unsigned GetQuartersAmount() const override;
		void IncQuarter() override;
		void DecQuarter() override;
		void GiveOutCoins() override;

	private:
		void SetSoldOutState() override;
		void SetNoQuarterState() override;
		void SetSoldState() override;
		void SetHasQuarterState() override;

	private:
		unsigned m_ballCount = 0;
		unsigned m_quarterCount = 0;
		std::unique_ptr<IState> m_currentState;
		std::ostream& m_out;
	};
} // namespace withState



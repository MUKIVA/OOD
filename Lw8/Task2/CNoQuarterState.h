#pragma once
#include "IState.h"
#include "IGumballMachine.h"

namespace withState
{
	class CNoQuarterState : public IState
	{
	public:
		CNoQuarterState(IGumballMachine& gumballMachine, std::ostream& out);

		void InsertQuarter();
		void EjectQuarter();
		void TurnCrank();
		void Dispense();
		void Refill(unsigned ballCount) override;
		std::string ToString() const;

	private:
		IGumballMachine& m_gumballMachine;
		std::ostream& m_out;
	};
}


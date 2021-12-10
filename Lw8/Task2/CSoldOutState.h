#pragma once
#include "IState.h"
#include "IGumballMachine.h"

namespace withState
{
	class CSoldOutState : public IState
	{
	public:
		CSoldOutState(IGumballMachine& gumballMachine, std::ostream& out);

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


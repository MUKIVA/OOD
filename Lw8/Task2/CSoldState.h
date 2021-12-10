#pragma once
#include "IGumballMachine.h"
#include "IState.h"

namespace withState
{
	class CSoldState : public IState
	{
	public:
		CSoldState(IGumballMachine& gumballMachine, std::ostream& out);

		void InsertQuarter() override;
		void EjectQuarter() override;
		void TurnCrank() override;
		void Dispense() override;
		void Refill(unsigned ballCount) override;
		std::string ToString() const;

	private:
		IGumballMachine& m_gumballMachine;
		std::ostream& m_out;
	};
}




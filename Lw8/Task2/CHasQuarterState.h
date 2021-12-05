#pragma once
#include "IGumballMachine.h"
#include "IState.h"

namespace withState
{
	class CHasQuarterState : public IState
	{
	public:
		CHasQuarterState(IGumballMachine& gumballMachine, std::ostream& out);

		void InsertQuarter() override;
		void EjectQuarter() override;
		void TurnCrank() override;
		void Dispense() override;
		std::string ToString() const;

	private:
		IGumballMachine& m_gumballMachine;
		std::ostream& m_out;
	};
}


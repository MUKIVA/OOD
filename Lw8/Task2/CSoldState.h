#pragma once
#include "IGumballMachine.h"
#include "IState.h"

namespace withState
{
	class CSoldState : public IState
	{
	public:
		CSoldState(IGumballMachine& gumballMachine, std::ostream& out);

		void InsertQuarter();
		void EjectQuarter();
		void TurnCrank();
		void Dispense();
		std::string ToString() const;

	private:
		IGumballMachine& m_gumballMachine;
		std::ostream& m_out;
	};
}




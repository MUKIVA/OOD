#pragma once
#include "IState.h"
#include "IGumballMachine.h"
#include "CSoldState.h"
#include "CSoldOutState.h"
#include "CNoQuarterState.h"
#include "CHasQuarterState.h"
#include <memory>
#include <iostream>

class CGumballMachine : public IGumballMachine
{
public:
	CGumballMachine(unsigned numBalls, std::ostream& out = std::cout);

	void InsertQuarter();
	void EjectQuarter();
	void TurnCrank();
	void Dispense();
	std::string ToString() const;


private:
	void ReleaseBall();
	unsigned GetBallCount() const;
	void SetSoldOutState();
	void SetNoQuarterState();
	void SetSoldState();
	void SetHasQuarterState();

private:
	unsigned m_count = 0;
	std::unique_ptr<IState> m_currentState;
	std::ostream& m_out;
};

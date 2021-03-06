#include <iostream>
#include <cstdint>
#include <functional>
#include "CMenu.h"
#include "CMultiGumballMachine.h"

using namespace withState;

class CGumballMachineController
{
public:
	CGumballMachineController(std::istream& in, std::ostream& out, unsigned startBallCount)
		: m_menu(in, out)
		, m_gumball(startBallCount, out)
		, m_in(in)
	{
		m_menu.AddItem("help", "	Show command list",				 [this]() { m_menu.ShowInstructions(); });
		m_menu.AddItem("exit", "	Exit",							 [this]() { m_menu.Exit(); });
		m_menu.AddItem("insert", "	Insert 1 quarter",				 std::bind(&CMultiGumballMachine::InsertQuarter, &m_gumball));
		m_menu.AddItem("eject", "	Eject 1 quarter",				 std::bind(&CMultiGumballMachine::EjectQuarter, &m_gumball));
		m_menu.AddItem("tc", "	Turn crank",						 std::bind(&CMultiGumballMachine::TurnCrank, &m_gumball));
		m_menu.AddItem("dis","	Give you gumball",					 std::bind(&CMultiGumballMachine::Dispense, &m_gumball));
		m_menu.AddItem("info", "	Give you gumball machine state", std::bind(&CMultiGumballMachine::ToString, &m_gumball));	
		m_menu.AddItem("refill", "	Refill gumball machine",		 std::bind(&CGumballMachineController::HandleRefill, this));
	}

	void HandleRefill()
	{
		unsigned ballCount;
		if (!(m_in >> ballCount))
			throw std::invalid_argument("Invalid argument count");

		m_gumball.Refill(ballCount);
	}

	void Start()
	{
		m_menu.Run();
	}

private:
	CMenu m_menu;
	CMultiGumballMachine m_gumball;
	unsigned m_ballForRefill = 0;
	std::istream& m_in;
};


int main()
{
	auto controller = CGumballMachineController(std::cin, std::cout, 20);
	controller.Start();

	return 0;
}
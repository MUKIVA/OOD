#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"

#include "../Task2/CMultiGumballMachine.h"
#include "../Task2/CNaiveMultiGumballMachine.h"

#include <iostream>
#include <string>
#include <sstream>

SCENARIO("WithState tests")
{
	using namespace withState;
	using namespace std;

	GIVEN("Gumball Machine is empty")
	{
		stringstream ss;
		CMultiGumballMachine m(0, ss);
		REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
								"C++-enabled Standing Gumball Model #2016 (with state)\n"
								"Inventory: 0 gumballs\n"
								"Quarters: 0\n"
								"Machine is sold out\n");
	
		WHEN("Dispense")
		{
			m.Dispense();
			REQUIRE(ss.str() == "No gumball dispensed\n");
		}
	
		WHEN("EjectQuarter")
		{
			m.EjectQuarter();
			REQUIRE(ss.str() == "You can't eject, you haven't inserted a quarter yet\n");
		}
	
		WHEN("GetBallCount")
		{
			IGumballMachine& iM = m;
			REQUIRE(iM.GetBallCount() == 0);
		}
		
		WHEN("InsertQuarter")
		{
			m.InsertQuarter();
			REQUIRE(ss.str() == "You can't insert a quarter, the machine is sold out\n");
		}
	
		WHEN("ReleaseBall")
		{
			IGumballMachine& iM = m;
			iM.ReleaseBall();
			REQUIRE(iM.GetBallCount() == 0);
		}

		WHEN("TurnCrank")
		{
			m.TurnCrank();
			REQUIRE(ss.str() == "You turned but there's no gumballs\n");
		}

		WHEN("Refill")
		{
			m.Refill(100);
			REQUIRE(m.GetBallCount() == 100);
		}
	}

	GIVEN("Gumball Machine filled with 1 gum")
	{
		stringstream ss;
		CMultiGumballMachine m(1, ss);
		REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
								"C++-enabled Standing Gumball Model #2016 (with state)\n"
								"Inventory: 1 gumball\n"
								"Quarters: 0\n"
								"Machine is waiting for quarter\n");
	
		WHEN("Dispense")
		{
			m.Dispense();
			REQUIRE(ss.str() == "You need to pay first\n");
		}

		WHEN("EjectQuarter")
		{
			m.EjectQuarter();
			REQUIRE(ss.str() == "You haven't inserted a quarter\n");
		}

		WHEN("GetBallCount")
		{
			IGumballMachine& iM = m;
			REQUIRE(iM.GetBallCount() == 1);
		}

		WHEN("InsertQuarter")
		{
			m.InsertQuarter();
			REQUIRE(ss.str() == "You inserted a quarter\n");
			REQUIRE(m.GetQuartersAmount() == 1);
		}

		WHEN("TurnCrank")
		{
			m.TurnCrank();
			REQUIRE(ss.str() == "You turned but there's no quarter\n");
		}

		WHEN("Refill")
		{
			m.Refill(100);
			REQUIRE(m.GetBallCount() == 100);
		}
	}

	GIVEN("Gumball Machine filled with 1 gum and 1 inserted quarter")
	{
		stringstream ss;
		CMultiGumballMachine m(1, ss);
		m.InsertQuarter();
		ss = stringstream("");
		REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
								"C++-enabled Standing Gumball Model #2016 (with state)\n"
								"Inventory: 1 gumball\n"
								"Quarters: 1\n"
								"Machine is waiting for turn of crank\n");
	
		WHEN("Dispense")
		{
			m.Dispense();
			REQUIRE(ss.str() == "No gumball dispensed\n");
		}
	
		WHEN("EjectQuarter")
		{
			m.EjectQuarter();
			REQUIRE(ss.str() == "Quarter returned\n");
		}
	
		WHEN("InsertQuarter")
		{
			m.InsertQuarter();
			REQUIRE(ss.str() == "You inserted a quarter\n");
		}
	
		WHEN("TurnCrank")
		{
			m.TurnCrank();
			REQUIRE(ss.str() == "You turned...\n");
		}

		WHEN("Refill")
		{
			m.Refill(100);
			REQUIRE(m.GetBallCount() == 100);
		}
	}

	GIVEN("Gumball Machine filled with 1 gum and 5 inserted quarter")
	{
		stringstream ss;
		CMultiGumballMachine m(1, ss);
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		ss = stringstream("");
		REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
								"C++-enabled Standing Gumball Model #2016 (with state)\n"
								"Inventory: 1 gumball\n"
								"Quarters: 5\n"
								"Machine is waiting for turn of crank\n");

		WHEN("Dispense")
		{
			m.Dispense();
			REQUIRE(ss.str() == "No gumball dispensed\n");
		}

		WHEN("EjectQuarter")
		{
			m.EjectQuarter();
			REQUIRE(ss.str() == "Quarter returned\n");
			REQUIRE(m.GetQuartersAmount() == 0);
		}

		WHEN("InsertQuarter")
		{
			m.InsertQuarter();
			REQUIRE(ss.str() == "You can't insert another quarter\n");
		}

		WHEN("TurnCrank")
		{
			m.TurnCrank();
			REQUIRE(ss.str() == "You turned...\n");
		}

		WHEN("DoubleTurnCrank")
		{
			m.TurnCrank();
			m.Dispense();
			m.TurnCrank();
			REQUIRE(ss.str() == "You turned...\n"
								"A gumball comes rolling out the slot...\n"
								"Oops, out of gumballs\n"
								"You turned but there's no gumballs\n"
			);
		}

		WHEN("Refill")
		{
			m.Refill(100);
			REQUIRE(m.GetBallCount() == 100);
		}
	}

	GIVEN("Gumball Machine filled with 2 gum and 5 inserted quarter")
	{
		stringstream ss;
		CMultiGumballMachine m(2, ss);
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		ss = stringstream("");
		REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
								"C++-enabled Standing Gumball Model #2016 (with state)\n"
								"Inventory: 2 gumballs\n"
								"Quarters: 5\n"
								"Machine is waiting for turn of crank\n");

		WHEN("Dispense")
		{
			m.Dispense();
			REQUIRE(ss.str() == "No gumball dispensed\n");
		}

		WHEN("EjectQuarter")
		{
			m.EjectQuarter();
			REQUIRE(ss.str() == "Quarter returned\n");
			REQUIRE(m.GetQuartersAmount() == 0);
		}

		WHEN("InsertQuarter")
		{
			m.InsertQuarter();
			REQUIRE(ss.str() == "You can't insert another quarter\n");
		}

		WHEN("TurnCrank")
		{
			m.TurnCrank();
			REQUIRE(ss.str() == "You turned...\n");
		}

		WHEN("DoubleTurnCrank")
		{
			m.TurnCrank();
			m.Dispense();
			m.TurnCrank();
			REQUIRE(ss.str() == "You turned...\n"
								"A gumball comes rolling out the slot...\n"
								"You turned...\n");
		}

		WHEN("Refill")
		{
			m.Refill(100);
			REQUIRE(m.GetBallCount() == 100);
		}
	}

	GIVEN("Gumball Machine with SOLD state")
	{
		stringstream ss;
		CMultiGumballMachine m(2, ss);
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.TurnCrank();
		ss = stringstream("");
		REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
								"C++-enabled Standing Gumball Model #2016 (with state)\n"
								"Inventory: 2 gumballs\n"
								"Quarters: 4\n"
								"Machine is delivering a gumball\n");
		WHEN("Refill")
		{
			m.Refill(100);
			REQUIRE(ss.str() == "You can't fill the gumball machine when it sells the ball\n");
		}
	}
}

SCENARIO("Naive tests")
{
	using namespace Naive;
	using namespace std;

	GIVEN("Gumball Machine is empty")
	{
		stringstream ss;
		CNaiveMultiGumballMachine m(0, ss);
		REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
								"C++-enabled Standing Gumball Model #2016 (with state)\n"
								"Inventory: 0 gumballs\n"
								"Quarters: 0\n"
								"Machine is sold out\n");

		WHEN("Dispense")
		{
			m.Dispense();
			REQUIRE(ss.str() == "No gumball dispensed\n");
		}

		WHEN("EjectQuarter")
		{
			m.EjectQuarter();
			REQUIRE(ss.str() == "You can't eject, you haven't inserted a quarter yet\n");
		}

		WHEN("InsertQuarter")
		{
			m.InsertQuarter();
			REQUIRE(ss.str() == "You can't insert a quarter, the machine is sold out\n");
		}

		WHEN("TurnCrank")
		{
			m.TurnCrank();
			REQUIRE(ss.str() == "You turned but there's no gumballs\n");
		}

		WHEN("Refill")
		{
			m.Refill(100);
			REQUIRE(m.GetBallCount() == 100);
		}
	}

	GIVEN("Gumball Machine filled with 1 gum")
	{
		stringstream ss;
		CNaiveMultiGumballMachine m(1, ss);
		REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
								"C++-enabled Standing Gumball Model #2016 (with state)\n"
								"Inventory: 1 gumball\n"
								"Quarters: 0\n"
								"Machine is waiting for quarter\n");

		WHEN("Dispense")
		{
			m.Dispense();
			REQUIRE(ss.str() == "You need to pay first\n");
		}

		WHEN("EjectQuarter")
		{
			m.EjectQuarter();
			REQUIRE(ss.str() == "You haven't inserted a quarter\n");
		}

		WHEN("InsertQuarter")
		{
			m.InsertQuarter();
			REQUIRE(ss.str() == "You inserted a quarter\n");
			REQUIRE(m.GetQuartersAmount() == 1);
		}

		WHEN("TurnCrank")
		{
			m.TurnCrank();
			REQUIRE(ss.str() == "You turned but there's no quarter\n");
		}

		WHEN("Refill")
		{
			m.Refill(100);
			REQUIRE(m.GetBallCount() == 100);
		}
	}

	GIVEN("Gumball Machine filled with 1 gum and 1 inserted quarter")
	{
		stringstream ss;
		CNaiveMultiGumballMachine m(1, ss);
		m.InsertQuarter();
		ss = stringstream("");
		REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
								"C++-enabled Standing Gumball Model #2016 (with state)\n"
								"Inventory: 1 gumball\n"
								"Quarters: 1\n"
								"Machine is waiting for turn of crank\n");

		WHEN("Dispense")
		{
			m.Dispense();
			REQUIRE(ss.str() == "No gumball dispensed\n");
		}

		WHEN("EjectQuarter")
		{
			m.EjectQuarter();
			REQUIRE(ss.str() == "Quarter returned\n");
		}

		WHEN("InsertQuarter")
		{
			m.InsertQuarter();
			REQUIRE(ss.str() == "You inserted a quarter\n");
		}

		WHEN("TurnCrank")
		{
			m.TurnCrank();
			REQUIRE(ss.str() == "You turned...\n");
		}

		WHEN("Refill")
		{
			m.Refill(100);
			REQUIRE(m.GetBallCount() == 100);
		}
	}

	GIVEN("Gumball Machine filled with 1 gum and 5 inserted quarter")
	{
		stringstream ss;
		CNaiveMultiGumballMachine m(1, ss);
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		ss = stringstream("");
		REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
								"C++-enabled Standing Gumball Model #2016 (with state)\n"
								"Inventory: 1 gumball\n"
								"Quarters: 5\n"
								"Machine is waiting for turn of crank\n");

		WHEN("Dispense")
		{
			m.Dispense();
			REQUIRE(ss.str() == "No gumball dispensed\n");
		}

		WHEN("EjectQuarter")
		{
			m.EjectQuarter();
			REQUIRE(ss.str() == "Quarter returned\n");
			REQUIRE(m.GetQuartersAmount() == 0);
		}

		WHEN("InsertQuarter")
		{
			m.InsertQuarter();
			REQUIRE(ss.str() == "You can't insert another quarter\n");
		}

		WHEN("TurnCrank")
		{
			m.TurnCrank();
			REQUIRE(ss.str() == "You turned...\n");
		}

		WHEN("DoubleTurnCrank")
		{
			m.TurnCrank();
			m.Dispense();
			m.TurnCrank();
			REQUIRE(ss.str() == "You turned...\n"
								"A gumball comes rolling out the slot...\n"
								"Oops, out of gumballs\n"
								"You turned but there's no gumballs\n");
		}

		WHEN("Refill")
		{
			m.Refill(100);
			REQUIRE(m.GetBallCount() == 100);
		}
	}

	GIVEN("Gumball Machine filled with 2 gum and 5 inserted quarter")
	{
		stringstream ss;
		CNaiveMultiGumballMachine m(2, ss);
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		ss = stringstream("");
		REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
								"C++-enabled Standing Gumball Model #2016 (with state)\n"
								"Inventory: 2 gumballs\n"
								"Quarters: 5\n"
								"Machine is waiting for turn of crank\n");

		WHEN("Dispense")
		{
			m.Dispense();
			REQUIRE(ss.str() == "No gumball dispensed\n");
		}

		WHEN("EjectQuarter")
		{
			m.EjectQuarter();
			REQUIRE(ss.str() == "Quarter returned\n");
			REQUIRE(m.GetQuartersAmount() == 0);
		}

		WHEN("InsertQuarter")
		{
			m.InsertQuarter();
			REQUIRE(ss.str() == "You can't insert another quarter\n");
		}

		WHEN("TurnCrank")
		{
			m.TurnCrank();
			REQUIRE(ss.str() == "You turned...\n");
		}

		WHEN("DoubleTurnCrank")
		{
			m.TurnCrank();
			m.Dispense();
			m.TurnCrank();
			REQUIRE(ss.str() == "You turned...\n"
								"A gumball comes rolling out the slot...\n"
								"You turned...\n");
		}

		WHEN("Refill")
		{
			m.Refill(100);
			REQUIRE(m.GetBallCount() == 100);
		}
	}

	GIVEN("Gumball Machine with SOLD state")
	{
		stringstream ss;
		CNaiveMultiGumballMachine m(2, ss);
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.InsertQuarter();
		m.TurnCrank();
		ss = stringstream("");
		REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
								"C++-enabled Standing Gumball Model #2016 (with state)\n"
								"Inventory: 2 gumballs\n"
								"Quarters: 4\n"
								"Machine is delivering a gumball\n");
		WHEN("Refill")
		{
			m.Refill(100);
			REQUIRE(ss.str() == "You can't fill the gumball machine when it sells the ball\n");
		}
	}
}
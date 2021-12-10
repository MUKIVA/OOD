#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"

#include "../Lw8/CGumballMachine.h"
#include "../Lw8/CHasQuarterState.h"
#include "../Lw8/CNoQuarterState.h"
#include "../Lw8/CSoldOutState.h"
#include "../Lw8/CSoldState.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

SCENARIO("Gumball Machine is empty")
{
	stringstream ss;
	CGumballMachine m(0, ss);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
							"C++-enabled Standing Gumball Model #2016 (with state)\n"
							"Inventory: 0 gumballs\n"
							"Machine is sold out\n");
	SECTION("Dispense")
	{
		m.Dispense();
		REQUIRE(ss.str() == "No gumball dispensed\n");
	}

	SECTION("EjectQuarter")
	{
		m.EjectQuarter();
		REQUIRE(ss.str() == "You can't eject, you haven't inserted a quarter yet\n");
	}

	SECTION("GetBallCount")
	{;
		REQUIRE(m.GetBallCount() == 0);
	}

	SECTION("InsertQuarter")
	{
		m.InsertQuarter();
		REQUIRE(ss.str() == "You can't insert a quarter, the machine is sold out\n");
	}

	SECTION("TurnCrank")
	{
		m.TurnCrank();
		REQUIRE(ss.str() == "You turned but there's no gumballs\n");
	}
}

SCENARIO("Gumball Machine filled with 1 gum")
{
	stringstream ss;
	CGumballMachine m(1, ss);
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
							"C++-enabled Standing Gumball Model #2016 (with state)\n"
							"Inventory: 1 gumball\n"
							"Machine is waiting for quarter\n");
	SECTION("Dispense")
	{
		m.Dispense();
		REQUIRE(ss.str() == "You need to pay first\n");
	}

	SECTION("EjectQuarter")
	{
		m.EjectQuarter();
		REQUIRE(ss.str() == "You haven't inserted a quarter\n");
	}

	SECTION("GetBallCount")
	{
		REQUIRE(m.GetBallCount() == 1);
	}

	SECTION("InsertQuarter")
	{
		m.InsertQuarter();
		REQUIRE(ss.str() == "You inserted a quarter\n");
	}

	SECTION("TurnCrank")
	{
		m.TurnCrank();
		REQUIRE(ss.str() == "You turned but there's no quarter\n");
	}
}

SCENARIO("Gumball Machine filled with 1 gum and 1 inserted quarter")
{
	stringstream ss;
	CGumballMachine m(1, ss);
	m.InsertQuarter();
	ss = stringstream("");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
							"C++-enabled Standing Gumball Model #2016 (with state)\n"
							"Inventory: 1 gumball\n"
							"Machine is waiting for turn of crank\n");
	SECTION("Dispense")
	{
		m.Dispense();
		REQUIRE(ss.str() == "No gumball dispensed\n");
	}

	SECTION("EjectQuarter")
	{
		m.EjectQuarter();
		REQUIRE(ss.str() == "Quarter returned\n");
	}

	SECTION("GetBallCount")
	{
		REQUIRE(m.GetBallCount() == 1);
	}

	SECTION("InsertQuarter")
	{
		m.InsertQuarter();
		REQUIRE(ss.str() == "You can't insert another quarter\n");
	}

	SECTION("TurnCrank")
	{
		m.TurnCrank();
		REQUIRE(ss.str() == "You turned...\n");
	}
}

SCENARIO("Gumball Machine filled with 1 gum and 1 turned quarter")
{
	stringstream ss;
	CGumballMachine m(1, ss);
	m.InsertQuarter();
	m.TurnCrank();
	ss = stringstream("");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
							"C++-enabled Standing Gumball Model #2016 (with state)\n"
							"Inventory: 1 gumball\n"
							"Machine is delivering a gumball\n");
	SECTION("Dispense")
	{
		m.Dispense();
		REQUIRE(ss.str() == "A gumball comes rolling out the slot...\n"
							"Oops, out of gumballs\n"
		);
	}

	SECTION("EjectQuarter")
	{
		m.EjectQuarter();
		REQUIRE(ss.str() == "Sorry you already turned the crank\n");
	}

	SECTION("GetBallCount")
	{
		REQUIRE(m.GetBallCount() == 1);
	}

	SECTION("InsertQuarter")
	{
		m.InsertQuarter();
		REQUIRE(ss.str() == "Please wait, we're already giving you a gumball\n");
	}

	SECTION("TurnCrank")
	{
		m.TurnCrank();
		REQUIRE(ss.str() == "Turning twice doesn't get you another gumball\n");
	}
}

SCENARIO("Gumball Machine filled with 1 gum and 1 turned quarter and dispense")
{
	stringstream ss;
	CGumballMachine m(1, ss);
	m.InsertQuarter();
	m.TurnCrank();
	m.Dispense();
	ss = stringstream("");
	REQUIRE(m.ToString() == "Mighty Gumball, Inc.\n"
							"C++-enabled Standing Gumball Model #2016 (with state)\n"
							"Inventory: 0 gumballs\n"
							"Machine is sold out\n");
	SECTION("Dispense")
	{
		m.Dispense();
		REQUIRE(ss.str() == "No gumball dispensed\n");
	}

	SECTION("EjectQuarter")
	{
		m.EjectQuarter();
		REQUIRE(ss.str() == "You can't eject, you haven't inserted a quarter yet\n");
	}

	SECTION("GetBallCount")
	{
		REQUIRE(m.GetBallCount() == 0);
	}

	SECTION("InsertQuarter")
	{
		m.InsertQuarter();
		REQUIRE(ss.str() == "You can't insert a quarter, the machine is sold out\n");
	}

	SECTION("TurnCrank")
	{
		m.TurnCrank();
		REQUIRE(ss.str() == "You turned but there's no gumballs\n");
	}
}

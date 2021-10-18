#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"

#include "../WeatherStation/Observer.h"
#include "../WeatherStation/WeatherData.h"

#include <set>
#include <sstream>
#include <string>

SCENARIO("Priority test")
{
	GIVEN("One weather station and two observers")
	{
		CStatsData one;
		CStatsData two;
		CWeatherData wd;

		WHEN("0 and 0")
		{
			std::set<WeatherContext> changed{WeatherContext::TEMPERATURE, WeatherContext::PRESSURE};
			wd.RegisterObserver(one, { WeatherContext::TEMPERATURE }, 0);
			wd.RegisterObserver(two, { WeatherContext::PRESSURE }, 0);

			REQUIRE(wd.GetPriorityMap().begin()->second == &one);
			REQUIRE((++wd.GetPriorityMap().begin())->second == &two);
		}

		WHEN("0 and 1")
		{
			std::set<WeatherContext> changed{ WeatherContext::TEMPERATURE, WeatherContext::PRESSURE };
			wd.RegisterObserver(one, { WeatherContext::TEMPERATURE }, 0);
			wd.RegisterObserver(two, { WeatherContext::PRESSURE }, 1);

			REQUIRE(wd.GetPriorityMap().begin()->second == &two);
			REQUIRE((++wd.GetPriorityMap().begin())->second == &one);
		}

		WHEN("1 and 0")
		{
			std::set<WeatherContext> changed{ WeatherContext::TEMPERATURE, WeatherContext::PRESSURE };
			wd.RegisterObserver(one, { WeatherContext::TEMPERATURE }, 1);
			wd.RegisterObserver(two, { WeatherContext::PRESSURE }, 0);

			REQUIRE(wd.GetPriorityMap().begin()->second == &one);
			REQUIRE((++wd.GetPriorityMap().begin())->second == &two);
		}

		WHEN("1 and 1")
		{
			std::set<WeatherContext> changed{ WeatherContext::TEMPERATURE, WeatherContext::PRESSURE };
			wd.RegisterObserver(one, { WeatherContext::TEMPERATURE }, 1);
			wd.RegisterObserver(two, { WeatherContext::PRESSURE }, 1);

			REQUIRE(wd.GetPriorityMap().begin()->second == &one);
			REQUIRE((++wd.GetPriorityMap().begin())->second == &two);
		}
	}
}

SCENARIO("Monitoring multiple subjects")
{
	GIVEN("two subjects and one observer")
	{
		CInsideWeatherData iwd;
		COutsideWeatherData owd;
		CDisplay allData;
		iwd.RegisterObserver(allData, {	WeatherContext::TEMPERATURE	});
		owd.RegisterObserver(allData, {	WeatherContext::TEMPERATURE });

		REQUIRE(iwd.GetPriorityMap().size() == 1);
		REQUIRE(owd.GetPriorityMap().size() == 1);

		std::stringstream ss;

		WHEN("Display from Inside")
		{
			allData.Display(&iwd, SWeatherInfo(), ss);
			std::string str = ss.str();
			REQUIRE(str.find("INSIDE") != std::string::npos);
		}

		WHEN("Display from Outside")
		{
			allData.Display(&owd, SWeatherInfo(), ss);
			std::string str = ss.str();
			REQUIRE(str.find("OUTSIDE") != std::string::npos);
		}
	}
}
#include "WeatherData.h"
#include <set>

int main()
{
	CInsideWeatherData wd;
	COutsideWeatherData outWd;
	CStatsData avS;
	//wd.RegisterObserver(allData, { WeatherContext::TEMPERATURE }, 2);
	//outWd.RegisterObserver(allData, { WeatherContext::TEMPERATURE }, 2);
	wd.RegisterObserver(avS, { WeatherContext::TEMPERATURE }, 1);
	outWd.RegisterObserver(avS, { WeatherContext::TEMPERATURE }, 1);

	wd.SetMeasurements(10, 0, 760);
	outWd.SetMeasurements(10, 0, 760, 10, 10);

	return 0;
}
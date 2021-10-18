#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

enum class WeatherContext
{
	TEMPERATURE,
	HUMIDITY,
	PRESSURE,
	WIND_DIRECTION,
	WIND_SPEED
};

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	int windDirection = 0;
	double windSpeed = 0;
	//const CObservable<SWeatherInfo, WeatherContext>* subject = nullptr;
};

class IDisplayable
{
	virtual void Display(const void* subject, SWeatherInfo const& data, std::ostream& os = std::cout) = 0;
};

class CWeatherData : public CObservable<SWeatherInfo, WeatherContext>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature() const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const
	{
		return m_pressure;
	}

	void MeasurementsChanged(std::set<WeatherContext> const& changed)
	{
		NotifyObservers(changed);
	}

	void SetMeasurements(double temp, double humidity, double pressure, std::set<WeatherContext>& changed)
	{
		
		if (m_humidity != humidity) changed.insert(WeatherContext::HUMIDITY);
		m_humidity = humidity;
		if (m_temperature != temp) changed.insert(WeatherContext::TEMPERATURE);
		m_temperature = temp;
		if (m_pressure != pressure) changed.insert(WeatherContext::PRESSURE);
		m_pressure = pressure;
		MeasurementsChanged(changed);
	}

	virtual std::string GetLocationInfo() const { return ""; };

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		//info.subject = this;
		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

class CDisplayAllData : IDisplayable
{
public:
	void Display(const void* subject, SWeatherInfo const& data, std::ostream& os = std::cout) override
	{
		os << "Info from: " << static_cast<const CWeatherData*>(subject)->GetLocationInfo() << std::endl;
		os << "Current Temp " << data.temperature << std::endl;
		os << "Current Hum " << data.humidity << std::endl;
		os << "Current Pressure " << data.pressure << std::endl;
		os << "----------------" << std::endl;
	}
};

class CDisplayAverageStats : IDisplayable
{

private:
	void CalculateStats()
	{
		m_min = std::min(m_min, m_value);
		m_max = std::max(m_max, m_value);
		m_acc += m_value;
		++m_countAcc;
	}

public:

	CDisplayAverageStats(std::string const& name, WeatherContext context)
		: m_displayName(name)
		, m_context(context)
	{
	}

	void Display(const void* subject, SWeatherInfo const& data, std::ostream& os = std::cout) override
	{
		switch (m_context)
		{
		case WeatherContext::TEMPERATURE:
				SetNewValue(data.temperature);
			break;
		case WeatherContext::HUMIDITY:
				SetNewValue(data.humidity);
			break;
		case WeatherContext::PRESSURE:
				SetNewValue(data.pressure);
			break;
		case WeatherContext::WIND_DIRECTION:
				SetNewValue(data.windDirection);
			break;
		case WeatherContext::WIND_SPEED:
				SetNewValue(data.windSpeed);
			break;
		default:
			break;
		}
		CalculateStats();

		os << "Info from: " << static_cast<const CWeatherData*>(subject)->GetLocationInfo() << std::endl;
		os << "Max " << m_displayName << " " << m_max << std::endl;
		os << "Min " << m_displayName << " " << m_max << std::endl;
		os << "Average " << m_displayName << " " << (m_acc / m_countAcc) << std::endl;
		os << "----------------" << std::endl;
	}

	void SetNewValue(double value)
	{
		m_value = value;
	}

private:
	WeatherContext m_context;
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	double m_value = 0;
	unsigned m_countAcc = 0;
	std::string m_displayName;

};

class CDisplay: public IObserver<SWeatherInfo>, public CDisplayAllData
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(const void* subject, SWeatherInfo const& data) override
	{
		Display(subject, data);	
	}
};

struct AllStats
{
	std::unique_ptr<CDisplayAverageStats> temp = std::make_unique<CDisplayAverageStats>("Temp", WeatherContext::TEMPERATURE);
	std::unique_ptr<CDisplayAverageStats> hum = std::make_unique<CDisplayAverageStats>("Hum", WeatherContext::HUMIDITY);
	std::unique_ptr<CDisplayAverageStats> press = std::make_unique<CDisplayAverageStats>("Press", WeatherContext::PRESSURE);
	std::unique_ptr<CDisplayAverageStats> windSpeed = std::make_unique<CDisplayAverageStats>("WindSpeed", WeatherContext::WIND_SPEED);
	std::unique_ptr<CDisplayAverageStats> windDirection = std::make_unique<CDisplayAverageStats>("WindDirection", WeatherContext::WIND_DIRECTION);
};

class CStatsData : public IObserver<SWeatherInfo>
{
public:
	void Update(const void* subject, SWeatherInfo const& data) override
	{
		m_subjects[subject].temp.get()->Display(subject, data);
		m_subjects[subject].hum.get()->Display(subject, data);
		m_subjects[subject].press.get()->Display(subject, data);
		m_subjects[subject].windDirection.get()->Display(subject, data);
		m_subjects[subject].windSpeed.get()->Display(subject, data);
	}

private:
	std::map<const void*, AllStats> m_subjects;
};

class CInsideWeatherData : public CWeatherData
{
public:
	std::string GetLocationInfo() const override
	{
		return "INSIDE";
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		std::set<WeatherContext> changed;
		CWeatherData::SetMeasurements(temp, humidity, pressure, changed);
	}
};

class COutsideWeatherData : public CWeatherData
{
public:
	std::string GetLocationInfo() const override
	{
		return "OUTSIDE";
	}

	int GetWindDirection() const
	{
		return m_windDirection % 360;
	}

	double GetWindSpeed() const
	{
		return m_windSpeed;
	}

	void SetMeasurements(double temp, double humidity, double pressure, int windDirection, double windSpeed)
	{
		std::set<WeatherContext> changed;
		if (m_windDirection != windDirection) changed.insert(WeatherContext::WIND_DIRECTION);
		m_windDirection = windDirection;
		if (m_windSpeed != windSpeed) changed.insert(WeatherContext::WIND_SPEED);
		m_windSpeed = windSpeed;
		CWeatherData::SetMeasurements(temp, humidity, pressure, changed);
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windDirection = GetWindDirection();
		info.windSpeed = GetWindSpeed();
		return info;
	}

private:
	int m_windDirection = 0;
	double m_windSpeed = 0;
};
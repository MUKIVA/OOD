#pragma once

#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string & description)
		:m_description(description)
	{}

	std::string GetDescription()const override final
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 60; 
	}
};


// Капуччино
class CCappuccino : public CCoffee
{
public:
	CCappuccino(const std::string& description = "Cappuccino") 
		:CCoffee("Cappuccino") 
	{}

	double GetCost() const override 
	{
		return 80; 
	}
};

class CDoubleCappuccino : public CCappuccino
{
public:
	CDoubleCappuccino(const std::string& description = "Double Cappuccino")
		: CCappuccino(description)
	{
	}

	double GetCost() const override
	{
		return 120;
	}
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(const std::string& description = "Latte") 
		:CCoffee(description) 
	{}

	double GetCost() const override 
	{
		return 90; 
	}
};

class CDoubleLatte : public CLatte
{
public:
	CDoubleLatte(const std::string& description = "Double Latte")
		: CLatte(description)
	{
	}

	double GetCost() const override
	{
		return 130;
	}
};

// Чай
class CTea : public CBeverage
{
public:
	CTea(const std::string& description = "Tea") 
		:CBeverage(description) 
	{}

	double GetCost() const override 
	{
		return 30; 
	}
};

class CWhiteTea : public CTea
{
public:
	CWhiteTea()
		: CTea("White Tea")
	{
	}
};

class CGreenTea : public CTea
{
public:
	CGreenTea()
		: CTea("Green Tea")
	{
	}
};

class CBlackTea : public CTea
{
public:
	CBlackTea()
		: CTea("Black Tea")
	{
	}
};

class CYellowTea : public CTea
{
public:
	CYellowTea()
		: CTea("Yellow Tea")
	{
	}
};

enum class MilkshakeType
{
	Small,	// Мелкий
	Medium, // Средний
	Large	// Большой
};

// Молочный коктейль
//class CMilkshake : public CBeverage
//{
//public:
//	CMilkshake(MilkshakeType type)
//	{
//		if (type == MilkshakeType::Small) CBeverage::CBeverage("asdasd");
//	}
//
//	double GetCost() const override
//	{
//		return 30;
//	}
//
//private:
//
//};

class CMilkshake : public CBeverage
{
public:
	CMilkshake(std::string const& description = "Milkshake")
		: CBeverage(description)
	{
	}
};


class CSmallMilkshake : public CMilkshake
{
public:
	CSmallMilkshake()
		: CMilkshake("Small Milkshake")
	{
	}

	double GetCost() const override
	{
		return 50;
	}
};

class CMediumMilkshake : public CMilkshake
{
public:
	CMediumMilkshake()
		: CMilkshake("Medium Milkshake")
	{
	}

	double GetCost() const override
	{
		return 60;
	}
};

class CLargeMilkshake : public CMilkshake
{
public:
	CLargeMilkshake()
		: CMilkshake("Large Milkshake")
	{
	}

	double GetCost() const override
	{
		return 80;
	}
};

#pragma once

namespace withState
{

	const unsigned MAX_QUARTERS = 5;

	class IGumballMachine
	{
	public:
		virtual void ReleaseBall() = 0;
		virtual unsigned GetBallCount() const = 0;
		virtual unsigned GetQuartersAmount() const = 0;
		virtual void IncQuarter() = 0;
		virtual void DecQuarter() = 0;
		virtual void GiveOutCoins() = 0;

		virtual void SetSoldOutState() = 0;
		virtual void SetNoQuarterState() = 0;
		virtual void SetSoldState() = 0;
		virtual void SetHasQuarterState() = 0;

		virtual ~IGumballMachine() = default;
	};
}



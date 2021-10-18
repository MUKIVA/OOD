#pragma once

#include "CShape.h"
#include "Point.h"

class CElipse : public CShape
{
public:
	CElipse(Color color, double hRadius, double wRadius, Point center)
		: m_horizontalRadius(hRadius)
		, m_verticalRadius(wRadius)
		, m_center(center)
		, CShape(color)
	{
		if (center.x < 0 || center.y < 0 || hRadius < 0 || wRadius < 0)
			throw std::invalid_argument("Invalid elipse arguments");
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawElipse(m_center, m_horizontalRadius, m_verticalRadius);
	}

	Point GetCenter() const
	{
		return m_center;
	}

	double GetHorizontalRadius() const
	{
		return m_horizontalRadius;
	}

	double GetVerticalRadius() const
	{
		return m_verticalRadius;
	}

private:
	double m_horizontalRadius = 0;
	double m_verticalRadius = 0;
	Point m_center;
};
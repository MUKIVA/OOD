#pragma once

#include "CShape.h"

class CTriangle : public CShape
{
public:
	CTriangle(Point p1, Point p2, Point p3, Color color)
		: m_p1(p1)
		, m_p2(p2)
		, m_p3(p3)
		, CShape(color)
	{
		if (p1.x < 0 || p1.y < 0
			|| p2.x < 0 || p2.y < 0
			|| p3.x < 0 || p3.y < 0)
			throw std::invalid_argument("Invalid triangle arguments");
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawLine(m_p1, m_p2);
		canvas.DrawLine(m_p2, m_p3);
		canvas.DrawLine(m_p3, m_p1);
	}

	Point GetVertex1() const
	{
		return m_p1;
	}

	Point GetVertex2() const
	{
		return m_p2;
	}

	Point GetVertex3() const
	{
		return m_p3;
	}

private:
	Point m_p1;
	Point m_p2;
	Point m_p3;
};
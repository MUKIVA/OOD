#pragma once

#include "CShape.h"
#include "Point.h"
#include <math.h>

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(Point center, unsigned int vertexCount, double radius, Color color)
		: m_center(center)
		, m_vertexCount(vertexCount)
		, m_radius(radius)
		, CShape(color)
	{
		if (vertexCount < 3 || radius < 0 || center.x < 0 || center.y < 0)
			throw std::invalid_argument("Invalid regular polygon arguments");
	}

	void Draw(ICanvas& canvas) const override
	{
		const double ANGLE = 3.1415926 * 2.f / m_vertexCount;
		Point prevPoint = { m_center.x, m_center.y - m_radius };
		for (unsigned int i = 0; i <= m_vertexCount; ++i)
		{
			Point newPoint = {
				m_radius * sin(ANGLE * i) + m_center.x,
				-m_radius * cos(ANGLE * i) + m_center.y
			};
			canvas.DrawLine(prevPoint, newPoint);
			prevPoint = newPoint;
		}	
	}

	Point GetCenter() const
	{
		return m_center;
	}

	unsigned int GetVertexCount() const
	{
		return m_vertexCount;
	}

	double GetRadius() const
	{
		return m_radius;
	}

private:
	Point m_center;
	unsigned int m_vertexCount = 3;
	double m_radius = 0;
};
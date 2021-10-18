#pragma once

#include "CShape.h"
#include "Point.h"


class CRectangle : public CShape
{
public:
	CRectangle(Point leftTop, Point rightBottom, Color color)
		: m_leftTop(leftTop)
		, m_rightBottom(rightBottom)
		, CShape(color)
	{
		if (leftTop.x < 0 || leftTop.y < 0 || rightBottom.x < 0 || rightBottom.y < 0)
			throw std::invalid_argument("invalid rectangle arguments");
	}

	void Draw(ICanvas& canvas) const override
	{
		canvas.DrawLine(m_leftTop, { m_leftTop.x, m_rightBottom.y });
		canvas.DrawLine(m_leftTop, { m_rightBottom.x, m_leftTop.y });
		canvas.DrawLine(m_rightBottom, { m_leftTop.x, m_rightBottom.y });
		canvas.DrawLine(m_rightBottom, { m_rightBottom.x, m_leftTop.y });
	}

	Point GetLeftTop() const
	{
		return m_leftTop;
	}

	Point GetRightBottom() const
	{
		return m_rightBottom;
	}

private:
	Point m_leftTop;
	Point m_rightBottom;
};
#pragma once
#include "CShape.h"
#include <stdexcept>

class CRectangle : public CShape
{
public:

	CRectangle(Point<double> const& topLeft, Point<double> const& bottomRight);
	
	void Draw(ICanvas& canvas) override;

protected:
	void MovePoints(double offsetX, double offsetY, double ratioWidth, double ratioHeight) override
	{
		m_topLeft.x += offsetX;
		m_topLeft.y += offsetY;

		m_bottomRight.x = (m_bottomRight.x - m_frame->topLeft.x) * ratioWidth + m_frame->topLeft.x;
		m_bottomRight.y = (m_bottomRight.y - m_frame->topLeft.y) * ratioHeight + m_frame->topLeft.y;

		m_bottomRight.x += offsetX;
		m_bottomRight.y += offsetY;
	}

private:
	Point<double> m_topLeft;
	Point<double> m_bottomRight;
};

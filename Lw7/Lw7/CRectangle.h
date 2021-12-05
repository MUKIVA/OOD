#pragma once
#include "CShape.h"
#include <stdexcept>

class CRectangle : public CShape
{
public:

	CRectangle(Point<double> const& topLeft, Point<double> const& bottomRight);
	
	void Draw(ICanvas& canvas) override;

protected:
	void MovePoints(double offsetX, double offsetY, double ratioWidth, double ratioHeight) override;
	

private:
	Point<double> m_topLeft;
	Point<double> m_bottomRight;
};

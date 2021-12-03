#pragma once
#include "CommonTypes.h"
#include "CShape.h"
#include <algorithm>
#include <stdexcept>

class CTriangle : public CShape
{
public:
	CTriangle(Point<double> const& p1, Point<double> const& p2, Point<double> const& p3);
	void Draw(ICanvas& canvas) override;

protected:
	void MovePoints(double offsetX, double offsetY, double ratioWidth, double ratioHeight) override;
	
private:
	Point<double> m_p1;
	Point<double> m_p2;
	Point<double> m_p3;
};

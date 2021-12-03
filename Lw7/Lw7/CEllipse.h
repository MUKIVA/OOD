#pragma once
#include "CShape.h"
#include <stdexcept>

class CEllipse : public CShape
{
public:
	CEllipse(Point<double> const& center, double width, double height);
	void Draw(ICanvas& canvas) override;

protected:
	void MovePoints(double offsetX, double offsetY, double ratioWidth, double ratioHeight) override;

private:
	Point<double> m_center;
	double m_width;
	double m_height;
};

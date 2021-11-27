#pragma once
#include "CommonTypes.h"
#include <vector>

class ICanvas
{
public:
	virtual void SetLineColor(RGBAColor color) = 0;
	virtual void SetFillColor(RGBAColor color) = 0;
	virtual void SetLineWidth(double width) = 0;
	virtual void MoveTo(Point<double> const& point) = 0;
	virtual void LineTo(Point<double> const& point) = 0;
	virtual void DrawEllipse(Point<double> const& center, double width, double height) = 0;
	virtual void FillEllipse(Point<double> const& center, double width, double height) = 0;
	virtual void FillPoligon(std::vector<Point<double>> points) = 0;

	virtual ~ICanvas() = default;
};

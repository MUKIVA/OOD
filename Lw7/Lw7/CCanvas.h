#pragma once
#include "ICanvas.h"
#include <iostream>

class CSvgCanvas : public ICanvas
{
public:
	CSvgCanvas(std::ostream& out)
		: m_out(out)
	{
		BeginDraw();
	}

	void SetLineColor(RGBAColor color);
	void SetFillColor(RGBAColor color);
	void SetLineWidth(double width);
	void MoveTo(Point<double> const& point);
	void LineTo(Point<double> const& point);
	void DrawEllipse(Point<double> const& center, double width, double height);
	void FillEllipse(Point<double> const& center, double width, double height);
	void FillPoligon(std::vector<Point<double>> points);

	~CSvgCanvas();

private:
	void BeginDraw();
	void EndDraw();

	std::ostream& m_out;
	RGBAColor m_lineColor = 0x000000;
	double m_lineWidth = 10;
	RGBAColor m_fillColor = 0x000000;
	Point<double> m_startPoint = {0, 0};
	size_t m_height = 1080;
	size_t m_width = 1920;
};

#pragma once

#include "ICanvas.h"
#include "Color.h"
#include <iostream>

class CCanvas : public ICanvas
{
public:
	CCanvas(std::ostream& outStream)
		: m_os(outStream)
	{
		m_os << "<svg "
				 << "xmlns='http://www.w3.org/2000/svg' "
				 << "width='" << m_canvasWidth << "' height='" << m_canvasHeight << "' "
				 << "viewPort='0 0 " << m_canvasWidth << " " << m_canvasHeight << "'>"
				 << std::endl;
	}

	CCanvas(std::ostream& outStream, unsigned int width, unsigned int height)
		: m_os(outStream)
		, m_canvasHeight(height)
		, m_canvasWidth(width)
	{
		m_os << "<svg "
				 << "xmlns='http://www.w3.org/2000/svg' "
				 << "width='" << m_canvasWidth << "' height='" << m_canvasHeight << "' "
				 << "viewPort='0 0 " << m_canvasWidth << " " << m_canvasHeight << "'>"
				 << std::endl;
	}

	void SetColor(Color color) override
	{
		m_color = color;
	}

	void DrawLine(Point from, Point to) const override
	{
		m_os << "<line "
			<< "x1 = '" << from.x << "' y1 = '" << from.y
			<< "' x2 = '" << to.x << "' y2 = '" << to.y << "' "
			<< "stroke = '" << COLOR_TO_STRING.at(m_color) << "' stroke-width = '5'/>"
			<< std::endl;
	}

	void DrawElipse(Point center, double w, double h) const override
	{
		m_os
			<< "<ellipse "
			<< "rx='" << w << "' ry='" << h << "' "
			<< "cx='" << center.x << "' cy='" << center.y << "' "
			<< "stroke='" << COLOR_TO_STRING.at(m_color) << "' stroke-width='5' "
			<< "fill='transparent' />"
			<< std::endl;
	}

	~CCanvas()
	{
		m_os << "</svg>" << std::endl;
	}

private:
	Color m_color = Color::BLACK;
	std::ostream& m_os;
	unsigned int m_canvasWidth = 1920;
	unsigned int m_canvasHeight = 1080;
};

#include "CCanvas.h"
#include <string>
#include <stdexcept>

std::string RgbaToString(RGBAColor color)
{
	int r = (color >> 16) & 0xff;
	int g = (color >> 8) & 0xff;
	int b = color & 0xff;
	return "rgb(" + std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b) + ")";
}

CSvgCanvas::~CSvgCanvas()
{
	EndDraw();
}

void CSvgCanvas::BeginDraw()
{
	m_out << "<svg "
		  << "xmlns='http://www.w3.org/2000/svg' "
		  << "width='" << m_width << "' height='" << m_height << "' "
		  << "viewPort='0 0 " << m_width << " " << m_height << "'>"
		  << std::endl;
}

void CSvgCanvas::EndDraw()
{
	m_out << "</svg>" << std::endl;
}

CSvgCanvas::CSvgCanvas(std::ostream& out)
	: m_out(out)
{
	BeginDraw();
}

void CSvgCanvas::SetLineColor(RGBAColor color)
{
	m_lineColor = color;
}

void CSvgCanvas::SetFillColor(RGBAColor color)
{
	m_fillColor = color;
}

void CSvgCanvas::SetLineWidth(double width)
{
	m_lineWidth = width;
}

void CSvgCanvas::MoveTo(Point<double> const& point)
{
	m_startPoint = point;
}

void CSvgCanvas::LineTo(Point<double> const& point)
{
	m_out << "<line "
		  << "x1 = '" << m_startPoint.x << "' y1 = '" << m_startPoint.y
		  << "' x2 = '" << point.x << "' y2 = '" << point.y << "' "
		  << "stroke = '" << RgbaToString(m_lineColor) << "' stroke-width = '" << m_lineWidth << "'/>"
		  << std::endl;
	m_startPoint = point;
}

void CSvgCanvas::DrawEllipse(Point<double> const& center, double width, double height)
{
	m_out << "<ellipse "
		  << "rx='" << width << "' ry='" << height << "' "
		  << "cx='" << center.x << "' cy='" << center.y << "' "
		  << "stroke='" << RgbaToString(m_lineColor) << "' stroke-width='" << m_lineWidth << "' "
		  << "fill-opacity='0"
		  << "' />"
		  << std::endl;
}

void CSvgCanvas::FillEllipse(Point<double> const& center, double width, double height)
{
	m_out << "<ellipse "
		  << "rx='" << width << "' ry='" << height << "' "
		  << "cx='" << center.x << "' cy='" << center.y << "' "
		  << "fill='" << RgbaToString(m_fillColor) << "' "
		  << "fill-opacity='1"
		  << "' />"
		  << std::endl;
}

void CSvgCanvas::FillPoligon(std::vector<Point<double>> points)
{
	if (points.empty())
		throw std::logic_error("FillPolygon with zero vertexes");

	std::string vertexesString;

	for (Point<double> point : points)
	{
		vertexesString.append(std::to_string(point.x)).append(",").append(std::to_string(point.y)).append(" ");
	}

	vertexesString.pop_back();

	m_out
		<< "<polygon "
		<< "points = '" << vertexesString << "' "
		<< "fill = '" << RgbaToString(m_fillColor) << "'/>" << std::endl;
}


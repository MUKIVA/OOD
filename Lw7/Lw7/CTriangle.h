#pragma once
#include "CommonTypes.h"
#include "CShape.h"
#include <algorithm>
#include <stdexcept>

class CTriangle : public CShape
{
public:
	CTriangle(Point<double> const& p1, Point<double> const& p2, Point<double> const& p3)
		: m_p1(p1)
		, m_p2(p2)
		, m_p3(p3)
	{
		double xCoords[] = { p1.x, p2.x, p3.x };
		double yCoords[] = { p1.y, p2.y, p3.y };
		double left = *std::min_element(xCoords, xCoords + 3);
		double right = *std::max_element(xCoords, xCoords + 3);
		double bottom = *std::max_element(yCoords, yCoords + 3);
		double top = *std::min_element(yCoords, yCoords + 3);
		RectD rect = {
			left,
			top,
			right - left,
			bottom - top,
		};
		SetFrame(rect);
	}


	void Draw(ICanvas& canvas) override
	{
		auto lineStyle = GetOutlineStyle();
		auto fillStyle = GetFillStyle();

		if (lineStyle == nullptr)
			throw std::logic_error("Invalid line style");

		if (fillStyle == nullptr)
			throw std::logic_error("Invalid fill style");

		if (*lineStyle->IsEnable())
		{
			canvas.SetLineColor(*lineStyle->GetColor());
			canvas.SetLineWidth(*lineStyle->GetLineWidth());
			canvas.MoveTo(m_p1);
			canvas.LineTo(m_p2);
			canvas.LineTo(m_p3);
			canvas.LineTo(m_p1);
		}

		if (*fillStyle->IsEnable())
		{
			canvas.SetFillColor(*fillStyle->GetColor());
			canvas.FillPoligon({ m_p1, m_p2, m_p3 });
		}
	}

protected:
	void MovePoints(double offsetX, double offsetY, double ratioWidth, double ratioHeight) override
	{
		m_p1.x = (m_p1.x - m_frame->topLeft.x) * ratioWidth + m_frame->topLeft.x;  m_p1.x += offsetX;
		m_p1.y = (m_p1.y - m_frame->topLeft.y) * ratioHeight + m_frame->topLeft.y; m_p1.y += offsetY;

		m_p2.x = (m_p2.x - m_frame->topLeft.x) * ratioWidth + m_frame->topLeft.x;  m_p2.x += offsetX;
		m_p2.y = (m_p2.y - m_frame->topLeft.y) * ratioHeight + m_frame->topLeft.y; m_p2.y += offsetY;

		m_p3.x = (m_p3.x - m_frame->topLeft.x) * ratioWidth + m_frame->topLeft.x;  m_p3.x += offsetX;
		m_p3.y = (m_p3.y - m_frame->topLeft.y) * ratioHeight + m_frame->topLeft.y; m_p3.y += offsetY;
	}
	
private:
	Point<double> m_p1;
	Point<double> m_p2;
	Point<double> m_p3;
};

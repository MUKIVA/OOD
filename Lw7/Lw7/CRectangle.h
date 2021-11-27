#pragma once
#include "CShape.h"
#include <stdexcept>

class CRectangle : public CShape
{
public:

	CRectangle(Point<double> const& topLeft, Point<double> const& bottomRight)
		: m_topLeft(topLeft)
		, m_bottomRight(bottomRight)
	{
		RectD rect = {
			{ topLeft.x, topLeft.y },
			bottomRight.x - topLeft.x,
			topLeft.y - bottomRight.y
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
			canvas.MoveTo(m_topLeft);
			canvas.LineTo({ m_bottomRight.x, m_topLeft.y });
			canvas.LineTo(m_bottomRight);
			canvas.LineTo({ m_topLeft.x, m_bottomRight.y });
			canvas.LineTo(m_topLeft);
		}

		if (*fillStyle->IsEnable())
		{
			canvas.SetFillColor(*fillStyle->GetColor());
			canvas.FillPoligon({ 
				m_topLeft,
				{ m_bottomRight.x, m_topLeft.y },
				m_bottomRight,
				{ m_topLeft.x, m_bottomRight.y } 
			});
		}
	}

private:
	Point<double> m_topLeft;
	Point<double> m_bottomRight;
};
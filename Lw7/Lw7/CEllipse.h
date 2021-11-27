#pragma once
#include "CShape.h"
#include <stdexcept>

class CEllipse : public CShape
{
public:
	CEllipse(Point<double> const& center, double width, double height)
		: m_center(center)
		, m_width(width)
		, m_height(height)
	{
		double top = center.y - height;
		double left = center.x - width;

		RectD rect = { { left, top }, width * 2, height * 2 };

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
			canvas.DrawEllipse(m_center, m_width, m_height);
		}

		if (*fillStyle->IsEnable())
		{
			canvas.SetFillColor(*fillStyle->GetColor());
			canvas.FillEllipse(m_center, m_width, m_height);
		}

	}

private:
	Point<double> m_center;
	double m_width;
	double m_height;
};

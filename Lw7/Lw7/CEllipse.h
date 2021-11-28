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

protected:
	void MovePoints(double offsetX, double offsetY, double ratioWidth, double ratioHeight) override
	{
		m_center.x = (m_center.x - m_frame->topLeft.x) * ratioWidth + m_frame->topLeft.x;
		m_center.y = (m_center.y - m_frame->topLeft.y) * ratioHeight + m_frame->topLeft.y;

		m_center.x += offsetX;
		m_center.y += offsetY;


		m_height *= ratioHeight;
		m_width *= ratioWidth;
	}

private:
	Point<double> m_center;
	double m_width;
	double m_height;
};

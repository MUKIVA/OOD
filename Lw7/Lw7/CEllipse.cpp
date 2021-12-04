#include "CEllipse.h"

CEllipse::CEllipse(Point<double> const& center, double width, double height)
	: m_center(center)
	, m_width(width)
	, m_height(height)
{
	double top = center.y - height;
	double left = center.x - width;

	RectD rect = { { left, top }, width * 2, height * 2 };

	SetFrame(rect);
}

void CEllipse::Draw(ICanvas& canvas)
{
	auto lineStyle = GetOutlineStyle();
	auto fillStyle = GetFillStyle();

	if (lineStyle.expired() || fillStyle.expired())
		throw std::logic_error("The style object has been deleted");

	if (*lineStyle.lock()->IsEnable())
	{
		canvas.SetLineColor(*lineStyle.lock()->GetColor());
		canvas.SetLineWidth(*lineStyle.lock()->GetLineWidth());
		canvas.DrawEllipse(m_center, m_width, m_height);
	}

	if (*fillStyle.lock()->IsEnable())
	{
		canvas.SetFillColor(*fillStyle.lock()->GetColor());
		canvas.FillEllipse(m_center, m_width, m_height);
	}
}

void CEllipse::MovePoints(double offsetX, double offsetY, double ratioWidth, double ratioHeight)
{
	m_center.x = (m_center.x - m_frame->topLeft.x) * ratioWidth + m_frame->topLeft.x;
	m_center.y = (m_center.y - m_frame->topLeft.y) * ratioHeight + m_frame->topLeft.y;

	m_center.x += offsetX;
	m_center.y += offsetY;

	m_height *= ratioHeight;
	m_width *= ratioWidth;
}

#include "CRectangle.h"

CRectangle::CRectangle(Point<double> const& topLeft, Point<double> const& bottomRight)
	: m_topLeft(topLeft)
	, m_bottomRight(bottomRight)
{
	RectD rect = {
		{ topLeft.x, topLeft.y },
		bottomRight.x - topLeft.x,
		bottomRight.y - topLeft.y
	};

	SetFrame(rect);
}

void CRectangle::Draw(ICanvas& canvas)
{
	auto lineStyle = GetOutlineStyle();
	auto fillStyle = GetFillStyle();

	if (lineStyle == nullptr || fillStyle == nullptr)
		throw std::logic_error("The style object has been deleted");

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

void CRectangle::MovePoints(double offsetX, double offsetY, double ratioWidth, double ratioHeight)
{
	m_topLeft.x += offsetX;
	m_topLeft.y += offsetY;

	m_bottomRight.x = (m_bottomRight.x - m_frame->topLeft.x) * ratioWidth + m_frame->topLeft.x;
	m_bottomRight.y = (m_bottomRight.y - m_frame->topLeft.y) * ratioHeight + m_frame->topLeft.y;

	m_bottomRight.x += offsetX;
	m_bottomRight.y += offsetY;
}

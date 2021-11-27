#include "COutlineStyle.h"

std::optional<bool> COutlineStyle::IsEnable() const
{
	return m_isEnable;
}

void COutlineStyle::Enable(bool enable)
{
	m_isEnable = enable;
}

std::optional<double> COutlineStyle::GetLineWidth() const
{
	return m_lineWidth;
}

void COutlineStyle::SetLineWidth(double width)
{
	m_lineWidth = width;
}


std::optional<RGBAColor> COutlineStyle::GetColor()
{
	return m_color;
}

void COutlineStyle::SetColor(RGBAColor color)
{
	m_color = color;
}

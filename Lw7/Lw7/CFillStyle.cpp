#include "CFillStyle.h"
#include <optional>

CFillStyle::CFillStyle(const IFillStyle& style)
	: m_color(style.GetColor())
	, m_isEnable(style.IsEnable())
{
	
}

CFillStyle::CFillStyle()
{

}

std::optional<bool> CFillStyle::IsEnable() const
{
	return m_isEnable;
}

void CFillStyle::Enable(bool enable)
{
	m_isEnable = enable;
}

std::optional<RGBAColor> CFillStyle::GetColor() const
{
	return m_color;
}

void CFillStyle::SetColor(RGBAColor color)
{
	m_color = color;
}

#include "CFillStyle.h"
#include <optional>

std::optional<bool> CFillStyle::IsEnable() const
{
	return m_isEnable;
}

void CFillStyle::Enable(bool enable)
{
	m_isEnable = enable;
}

std::optional<RGBAColor> CFillStyle::GetColor()
{
	return m_color;
}

void CFillStyle::SetColor(RGBAColor color)
{
	m_color = color;
}

#include "CGroupFillStyle.h"

CGroupFillStyle::CGroupFillStyle(std::vector<std::shared_ptr<IShape>> shapes, std::optional<RGBAColor> color,
									std::optional<bool> isEnable)
	: m_shapes(shapes)
	, m_isEnable(isEnable)
	, m_color(color)
{
}

std::optional<bool> CGroupFillStyle::IsEnable() const
{
	return m_isEnable;
}

void CGroupFillStyle::Enable(bool enable)
{
	for (auto& shape : m_shapes)
	{
		auto shapeFillStyle = shape->GetFillStyle();
		shapeFillStyle->Enable(enable);
	}

	m_isEnable = enable;
}

std::optional<RGBAColor> CGroupFillStyle::GetColor()
{
	return m_color;
}

void CGroupFillStyle::SetColor(RGBAColor color)
{
	for (auto& shape : m_shapes)
	{
		auto shapeFillStyle = shape->GetFillStyle();
		shapeFillStyle->SetColor(color);
	}

	m_color = color;
}

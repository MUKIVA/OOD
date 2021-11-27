#include "CGroupOutlineStyle.h"

CGroupOutlineStyle::CGroupOutlineStyle(std::vector<std::shared_ptr<IShape>> shapes, std::optional<RGBAColor> color, std::optional<double> width, std::optional<bool> isEnable)
	: m_shapes(shapes)
	, m_color(color)
	, m_isEnable(isEnable)
	, m_lineWidth(width)
{
}

std::optional<bool> CGroupOutlineStyle::IsEnable() const
{
	return m_isEnable;
}

void CGroupOutlineStyle::Enable(bool enable)
{
	for (auto& shape : m_shapes)
	{
		auto shapeLineStyle = shape->GetOutlineStyle();
		shapeLineStyle->Enable(enable);
	}

	m_isEnable = enable;
}

std::optional<double> CGroupOutlineStyle::GetLineWidth() const
{
	return m_lineWidth;
}

void CGroupOutlineStyle::SetLineWidth(double width)
{
	for (auto& shape : m_shapes)
	{
		auto shapeLineStyle = shape->GetOutlineStyle();
		shapeLineStyle->SetLineWidth(width);
	}

	m_lineWidth = width;
}

std::optional<RGBAColor> CGroupOutlineStyle::GetColor()
{
	return m_color;
}

void CGroupOutlineStyle::SetColor(RGBAColor color)
{
	for (auto& shape : m_shapes)
	{
		auto shapeLineStyle = shape->GetOutlineStyle();
		shapeLineStyle->SetColor(color);
	}

	m_color = color;
}

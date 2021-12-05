#include "CGroupFillStyle.h"

CGroupFillStyle::CGroupFillStyle(std::shared_ptr<IFillStyleEnumerated> enumerator)
	: m_enum(enumerator)
{
}

std::optional<bool> CGroupFillStyle::IsEnable() const
{
	std::optional<bool> result = std::nullopt;
	bool first = true;
	m_enum->EnumerateFillStyles([&result, &first](IFillStyle& style) 
	{
		if (first)
		{
			result = style.IsEnable();
			first = false;
			return;
		}

		if (result == std::nullopt)
			return;

		result = (result != style.IsEnable()) ? std::nullopt : style.IsEnable();
	});

	return result;
}

void CGroupFillStyle::Enable(bool enable)
{
	m_enum->EnumerateFillStyles([enable](IFillStyle& style) 
	{
		style.Enable(enable);
	});
}

std::optional<RGBAColor> CGroupFillStyle::GetColor() const
{
	std::optional<RGBAColor> result = std::nullopt;
	bool first = true;
	m_enum->EnumerateFillStyles([&result, &first](IFillStyle& style)
	{
		if (first)
		{
			result = style.GetColor();
			first = false;
			return;
		}

		if (result == std::nullopt)
			return;
		
		result = (result != style.GetColor()) ? std::nullopt : style.GetColor();
	});

	return result;
}

void CGroupFillStyle::SetColor(RGBAColor color)
{
	m_enum->EnumerateFillStyles([color](IFillStyle& style) 
	{
		style.SetColor(color);
	});
}

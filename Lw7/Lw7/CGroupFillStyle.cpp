#include "CGroupFillStyle.h"

CGroupFillStyle::CGroupFillStyle(const std::shared_ptr<IFillStyleEnumerated>& enumerator)
	: m_enum(enumerator)
{
}

std::optional<bool> CGroupFillStyle::IsEnable() const
{
	std::optional<bool> result = true;
	bool first = true;
	m_enum->EnumerateFillStyles([&result, &first](IFillStyle& style) 
	{
		if (result == std::nullopt)
			return;

		if (first)
		{
			result = style.IsEnable();
			first = false;
			return;
		}

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

std::optional<RGBAColor> CGroupFillStyle::GetColor()
{
	std::optional<RGBAColor> result = true;
	bool first = true;
	m_enum->EnumerateFillStyles([&result, &first](IFillStyle& style)
	{
		if (result == std::nullopt)
			return;

		if (first)
		{
			result = style.GetColor();
			first = false;
			return;
		}
		
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

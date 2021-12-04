#include "CGroupOutlineStyle.h"

CGroupOutlineStyle::CGroupOutlineStyle(std::shared_ptr<IOutlineStyleEnumerated> enumerator)
	: m_enum(enumerator)
{
}

std::optional<bool> CGroupOutlineStyle::IsEnable() const
{
	std::optional<bool> result = std::nullopt;
	bool first = true;
	m_enum->EnumerateOutlineStyles([&result, &first](IOutlineStyle& style)
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

void CGroupOutlineStyle::Enable(bool enable)
{
	m_enum->EnumerateOutlineStyles([enable](IOutlineStyle& style) 
	{
		style.Enable(enable);
	});
}

std::optional<double> CGroupOutlineStyle::GetLineWidth() const
{
	std::optional<double> result = std::nullopt;
	bool first = true;
	m_enum->EnumerateOutlineStyles([&result, &first](IOutlineStyle& style)
	{
		if (first)
		{
			result = style.GetLineWidth();
			first = false;
			return;
		}

		if (result == std::nullopt)
			return;

		result = (result != style.GetLineWidth()) ? std::nullopt : style.GetLineWidth();
	});

	return result;
}

void CGroupOutlineStyle::SetLineWidth(double width)
{
	m_enum->EnumerateOutlineStyles([width](IOutlineStyle& style) 
	{
		style.SetLineWidth(width);
	});
}

std::optional<RGBAColor> CGroupOutlineStyle::GetColor()
{
	std::optional<RGBAColor> result = std::nullopt;
	bool first = true;
	m_enum->EnumerateOutlineStyles([&result, &first](IOutlineStyle& style)
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

void CGroupOutlineStyle::SetColor(RGBAColor color)
{
	m_enum->EnumerateOutlineStyles([color](IOutlineStyle& style) 
	{
		style.SetColor(color);
	});
}

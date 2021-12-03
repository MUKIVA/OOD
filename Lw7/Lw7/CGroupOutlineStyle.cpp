#include "CGroupOutlineStyle.h"

CGroupOutlineStyle::CGroupOutlineStyle(const std::shared_ptr<IOutlineStyleEnumerated>& enumerator)
	: m_enum(move(enumerator))
{
}

std::optional<bool> CGroupOutlineStyle::IsEnable() const
{
	std::optional<bool> result = true;
	bool first = true;
	m_enum->EnumerateOutlineStyles([&result, &first](IOutlineStyle& style)
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

void CGroupOutlineStyle::Enable(bool enable)
{
	m_enum->EnumerateOutlineStyles([enable](IOutlineStyle& style) 
	{
		style.Enable(enable);
	});
}

std::optional<double> CGroupOutlineStyle::GetLineWidth() const
{
	std::optional<double> result;
	bool first = true;
	m_enum->EnumerateOutlineStyles([&result, &first](IOutlineStyle& style)
	{
		if (result == std::nullopt)
			return;

		if (first)
		{
			result = style.GetLineWidth();
			first = false;
			return;
		}

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
	std::optional<RGBAColor> result;
	bool first = true;
	m_enum->EnumerateOutlineStyles([&result, &first](IOutlineStyle& style)
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

void CGroupOutlineStyle::SetColor(RGBAColor color)
{
	m_enum->EnumerateOutlineStyles([color](IOutlineStyle& style) 
	{
		style.SetColor(color);
	});
}

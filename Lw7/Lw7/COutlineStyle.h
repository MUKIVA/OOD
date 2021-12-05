#pragma once
#include "CommonTypes.h"
#include "IOutlineStyle.h"
#include <optional>

class COutlineStyle : public IOutlineStyle
{
public:

	COutlineStyle(const IOutlineStyle& style);
	COutlineStyle();

	std::optional<bool> IsEnable() const override;
	void Enable(bool enable) override;

	std::optional<double> GetLineWidth() const override;
	void SetLineWidth(double width) override;

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

private:
	std::optional<RGBAColor> m_color = 0x000000;
	std::optional<double> m_lineWidth = 5;
	std::optional<bool> m_isEnable = true;
};

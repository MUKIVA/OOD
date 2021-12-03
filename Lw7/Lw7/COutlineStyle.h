#pragma once
#include "CommonTypes.h"

class COutlineStyle : public IOutlineStyle
{
public:

	std::optional<bool> IsEnable() const override;
	void Enable(bool enable) override;

	std::optional<double> GetLineWidth() const override;
	void SetLineWidth(double width) override;

	std::optional<RGBAColor> GetColor() override;
	void SetColor(RGBAColor color) override;

private:
	std::optional<RGBAColor> m_color = 0x000000;
	std::optional<double> m_lineWidth = 5;
	std::optional<bool> m_isEnable = true;
};

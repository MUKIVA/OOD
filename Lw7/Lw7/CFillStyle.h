#pragma once
#include "CommonTypes.h"
#include "IFillStyle.h"

class CFillStyle : public IFillStyle
{
public:
	CFillStyle(const IFillStyle& style);
	CFillStyle();

	std::optional<bool> IsEnable() const override;
	void Enable(bool enable) override;

	std::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

private:
	std::optional<RGBAColor> m_color = 0x000000;
	std::optional<bool> m_isEnable = true;
};

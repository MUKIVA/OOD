#pragma once
#include "IShape.h"
#include "IFillStyle.h"
#include "IFillStyleEnumerated.h"
#include <vector>

class CGroupFillStyle : public IFillStyle
{
public:
	CGroupFillStyle(const std::shared_ptr<IFillStyleEnumerated>& enumerator);

	std::optional<bool> IsEnable() const;
	void Enable(bool enable);
	std::optional<RGBAColor> GetColor();
	void SetColor(RGBAColor color);

private:
	std::shared_ptr<IFillStyleEnumerated> m_enum;
};

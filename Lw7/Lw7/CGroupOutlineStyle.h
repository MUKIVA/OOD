#pragma once
#include "IOutlineStyle.h"
#include "IOutlineStyleEnumerated.h"
#include "IShape.h"
#include <vector>

class CGroupOutlineStyle : public IOutlineStyle
{
public:

	CGroupOutlineStyle(const std::shared_ptr<IOutlineStyleEnumerated> enumerator);

	std::optional<bool> IsEnable() const override;
	void Enable(bool enable) override;
	std::optional<double> GetLineWidth() const override;
	void SetLineWidth(double width) override;
	std::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

private:
	std::shared_ptr<IOutlineStyleEnumerated> m_enum;
};


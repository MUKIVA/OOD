#pragma once
#include "IShape.h"
#include "IStyle.h"
#include <vector>

class CGroupFillStyle : public IFillStyle
{
public:
	CGroupFillStyle(std::vector<std::shared_ptr<IShape>> shapes, std::optional<RGBAColor> color, std::optional<bool> isEnable);

	std::optional<bool> IsEnable() const;
	void Enable(bool enable);
	std::optional<RGBAColor> GetColor();
	void SetColor(RGBAColor color);

private:
	std::optional<RGBAColor> m_color;
	std::optional<bool> m_isEnable;
	std::vector<std::shared_ptr<IShape>> m_shapes;

};

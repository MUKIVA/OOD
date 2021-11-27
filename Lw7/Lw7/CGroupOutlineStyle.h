#pragma once
#include "IStyle.h"
#include "IShape.h"
#include <vector>

class CGroupOutlineStyle : public IOutlineStyle
{
public:
	CGroupOutlineStyle(std::vector<std::shared_ptr<IShape>> shapes, std::optional<RGBAColor> color,
		std::optional<double> width, std::optional<bool> isEnable);

	std::optional<bool> IsEnable() const;
	void Enable(bool enable);
	std::optional<double> GetLineWidth() const;
	void SetLineWidth(double width);
	std::optional<RGBAColor> GetColor();
	void SetColor(RGBAColor color);

private:
	std::optional<RGBAColor> m_color;
	std::optional<double> m_lineWidth;
	std::optional<bool> m_isEnable;
	std::vector<std::shared_ptr<IShape>> m_shapes;
};


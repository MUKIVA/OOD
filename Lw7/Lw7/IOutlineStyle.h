#pragma once
#include <optional>
#include "CommonTypes.h"


class IOutlineStyle
{
public:
	virtual std::optional<bool> IsEnable() const = 0;
	virtual void Enable(bool enable) = 0;

	virtual std::optional<double> GetLineWidth() const = 0;
	virtual void SetLineWidth(double width) = 0;
	virtual std::optional<RGBAColor> GetColor() const = 0;
	virtual void SetColor(RGBAColor color) = 0;

	~IOutlineStyle() = default;
};
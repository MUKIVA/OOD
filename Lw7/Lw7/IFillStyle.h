#pragma once
#include "CommonTypes.h"
#include <optional>

class IFillStyle
{
public:

	virtual std::optional<bool> IsEnable() const = 0;
	virtual void Enable(bool enable) = 0;
	virtual std::optional<RGBAColor> GetColor() = 0;
	virtual void SetColor(RGBAColor color) = 0;

	~IFillStyle() = default;
};


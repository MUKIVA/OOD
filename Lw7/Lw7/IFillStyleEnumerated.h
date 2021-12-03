#pragma once
#include <functional>
#include "IFillStyle.h"

class IFillStyleEnumerated
{
public:
	virtual void EnumerateFillStyles(const std::function<void(IFillStyle& style)>& callback) const = 0;
};
#pragma once
#include <functional>
#include "IOutlineStyle.h"

class IOutlineStyleEnumerated
{
public:
	virtual void EnumerateOutlineStyles(const std::function<void(IOutlineStyle& style)>& callback) const = 0;
	virtual ~IOutlineStyleEnumerated() = default;
};
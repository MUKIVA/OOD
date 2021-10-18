#pragma once

#include <memory>
#include "CShape.h"
#include <string>

class IShapeFactory
{
public:
	virtual std::unique_ptr<CShape> CreateShape(std::string const& description) = 0;
	virtual ~IShapeFactory() = default;
};
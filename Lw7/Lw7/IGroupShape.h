#pragma once
#include "IShape.h"
#include "IShapes.h"
#include "IFillStyleEnumerated.h"
#include "IOutlineStyleEnumerated.h"

class IGroupShape 
	: public IShape
	, public IShapes
	, public IFillStyleEnumerated
	, public IOutlineStyleEnumerated
{
public:
	virtual ~IGroupShape() = default;
};

#pragma once
#include "CommonTypes.h"
#include "ICanvas.h"

class IDrawable
{
public:
	virtual void Draw(ICanvas& canvas) = 0;

	virtual ~IDrawable() = default;
};

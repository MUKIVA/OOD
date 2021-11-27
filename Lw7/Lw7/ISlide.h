#pragma once
#include "CommonTypes.h"
#include "IShapes.h"
#include "IDrawable.h"
#include "IShapes.h"

class ISlide : public IDrawable, public IShapes 
{
public:
	virtual size_t GetWidth() const = 0;
	virtual size_t GetHeight() const = 0;

	virtual void ResizeSlide(size_t width, size_t height) = 0;
	
	virtual ~ISlide() = default;
};
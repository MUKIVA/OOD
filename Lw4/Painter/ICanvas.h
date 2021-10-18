#pragma once
#include "Color.h"
#include "Point.h"

class ICanvas
{
public:
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(Point from, Point to) const = 0;
	virtual void DrawElipse(Point center, double w, double h) const = 0;
	virtual ~ICanvas() = default;
};
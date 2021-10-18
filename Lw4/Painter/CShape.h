#pragma once

#include "ICanvas.h"

class CShape
{
public:
	CShape(Color color)
		: m_color(color)
	{}
	Color GetColor() const
	{
		return m_color;
	}
	virtual void Draw(ICanvas& canvas) const = 0;
	virtual ~CShape() = default;

protected:
	Color m_color;
};
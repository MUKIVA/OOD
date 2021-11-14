#pragma once

#include "../Lw6/GraphicsLib.h"
#include "../Lw6/ModernGraphicsLib.h"
#include <iostream>

class CClassRendererAdapter : public graphics_lib::ICanvas
	, public modern_graphics_lib::CModernGraphicsRenderer
{
public:
	CClassRendererAdapter(std::ostream& strm)
		: m_start(0, 0)
		, modern_graphics_lib::CModernGraphicsRenderer(strm)
	{
	}

	void MoveTo(int x, int y) override
	{
		m_start = { x, y };
	}

	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint end(x, y);
		DrawLine(m_start, end);
		m_start = end;
	}

private:
	modern_graphics_lib::CPoint m_start;
};
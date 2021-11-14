#pragma once
#include "ModernGraphicsLib.h"
#include "GraphicsLib.h"
#include <memory>

class CRendererAdapter : public graphics_lib::ICanvas
{
public:
	CRendererAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer)
		: m_renderer(renderer)
		, m_start(0, 0)
	{
	}

	void MoveTo(int x, int y) override
	{
		m_start = { x, y };
	}

	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint endPoint(x, y); 
		m_renderer.DrawLine(m_start, endPoint);
		m_start = endPoint;
	}

private:
	modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
	modern_graphics_lib::CPoint m_start;
};

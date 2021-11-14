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
		, m_color(0.0f, 0.0f, 0.0f, 0.0f)
	{
	}

	void MoveTo(int x, int y) override
	{
		m_start = { x, y };
	}

	void LineTo(int x, int y) override
	{
		modern_graphics_lib::CPoint endPoint(x, y); 
		m_renderer.DrawLine(m_start, endPoint, m_color);
		m_start = endPoint;
	}

	void SetColor(std::uint32_t color) override
	{
		float r = (float)((color >> 16) & 0xff) / 255;
		float g = (float)((color >> 8) & 0xff) / 255;
		float b = (float)((color >> 0) & 0xff) / 255;
		m_color = modern_graphics_lib::CRGBAColor(r, g, b, 0.0f);
	}

private:
	modern_graphics_lib::CModernGraphicsRenderer& m_renderer;
	modern_graphics_lib::CPoint m_start;
	modern_graphics_lib::CRGBAColor m_color;
};

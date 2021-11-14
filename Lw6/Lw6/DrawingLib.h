#pragma once
#include <iostream>
#include "GraphicsLib.h"

// Пространство имен библиотеки для рисования фигур (использует graphics_lib)
// Код библиотеки недоступен для изменения
namespace shape_drawing_lib
{

	struct Point
	{
		int x = 0;
		int y = 0;
	};
	// Интерфейс объектов, которые могут быть нарисованы на холсте из graphics_lib
	class ICanvasDrawable
	{
	public:
		virtual void Draw(graphics_lib::ICanvas& canvas) const = 0;
		virtual ~ICanvasDrawable() = default;
	};

	class CTriangle : public ICanvasDrawable
	{
	public:
		CTriangle(Point const& p1, Point const& p2, Point const& p3)
			: m_p1(p1)
			, m_p2(p2)
			, m_p3(p3)
		{
		}

		void Draw(graphics_lib::ICanvas& canvas) const override
		{
			canvas.MoveTo(m_p1.x, m_p1.y);
			canvas.LineTo(m_p2.x, m_p2.y);
			canvas.LineTo(m_p3.x, m_p3.y);
			canvas.LineTo(m_p1.x, m_p1.y);
		}

	private:
		Point m_p1;
		Point m_p2;
		Point m_p3;
	};

	class CRectangle : public ICanvasDrawable
	{
	public:
		CRectangle(Point const& topLeft, Point const& bottomRight)
			: m_bottomRight(bottomRight)
			, m_topLeft(topLeft)
		{
		}

		void Draw(graphics_lib::ICanvas& canvas) const override
		{
			canvas.MoveTo(m_topLeft.x, m_topLeft.y);
			canvas.LineTo(m_bottomRight.x, m_topLeft.y);
			canvas.LineTo(m_bottomRight.x, m_bottomRight.y);
			canvas.LineTo(m_topLeft.x, m_bottomRight.y);
			canvas.LineTo(m_topLeft.x, m_topLeft.y);
		}

	private:
		Point m_topLeft;
		Point m_bottomRight;
	};

	// Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
	class CCanvasPainter
	{
	public:
		CCanvasPainter(graphics_lib::ICanvas& canvas)
			: m_canvas(canvas)
		{
		}

		void Draw(ICanvasDrawable const& drawable)
		{
			drawable.Draw(m_canvas);
		}

	private:
		graphics_lib::ICanvas& m_canvas;
	};
}
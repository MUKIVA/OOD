#pragma once

#include "CRendererAdapter.h"
#include "DrawingLib.h"
#include "GraphicsLib.h"
#include "ModernGraphicsLib.h"

// Пространство имен приложения (доступно для модификации)
namespace app
{
	void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
	{
		using namespace shape_drawing_lib;
		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0xff0000);
		CRectangle rectangle({ 30, 40 }, { 18, 24 });
	
		painter.Draw(triangle);
		painter.Draw(rectangle);
	}

	void PaintPictureOnCanvas()
	{
		graphics_lib::CCanvas simpleCanvas;
		shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
		PaintPicture(painter);
	}

	void PaintPictureOnModernGraphicsRenderer()
	{
		modern_graphics_lib::CModernGraphicsRenderer renderer(std::cout);
		auto a = CRendererAdapter(renderer);
		shape_drawing_lib::CCanvasPainter painter(a);
		PaintPicture(painter);
	}
} // namespace app
#pragma once

#include "../Lw6/DrawingLib.h"
#include "../Lw6/GraphicsLib.h"
#include "../Lw6/ModernGraphicsLib.h"
#include "CClassRendererAdapter.h"

// Пространство имен приложения (доступно для модификации)
namespace app
{
void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
{
	using namespace shape_drawing_lib;

	CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
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
	CClassRendererAdapter renderer(std::cout);
	shape_drawing_lib::CCanvasPainter painter(renderer);
	PaintPicture(painter);
}
} // namespace app
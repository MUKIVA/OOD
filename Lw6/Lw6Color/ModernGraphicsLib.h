#pragma once
#include <iostream>
#include <exception>
#include <format>
#include <cassert>
#include <iomanip>

// Пространство имен современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib
{
	class CPoint
	{
	public: 
		CPoint(int x, int y): x(x), y(y) {} 

		int x;
		int y;
	};

	// Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
	class CRGBAColor
	{
	public:
		CRGBAColor(float r, float g, float b, float a)
			: r(r)
			, g(g)
			, b(b)
			, a(a)
		{
			assert(r >= 0.0f && r <= 1.0f);
			assert(g >= 0.0f && g <= 1.0f);
			assert(b >= 0.0f && b <= 1.0f);
			assert(a >= 0.0f && a <= 1.0f);
		}
		float r, g, b, a;
	};
	
	//Класс для современного рисования графики
	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(std::ostream& strm): m_out(strm){}

		~CModernGraphicsRenderer()
		{
			if (m_drawing) // Завершаем рисование, если оно было начато
			{
				EndDraw();
			}
		}

		void BeginDraw()
		{
			if (m_drawing)
			{
				throw std::logic_error("Drawing has already begun");
			}

			m_out << "<draw>" << std::endl;
			m_drawing = true;
		}


		void DrawLine(CPoint const& start, CPoint const& end, CRGBAColor const& color)
		{
			if (m_drawing)
			{
				throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
			}

			m_out << std::format("<line fromX=\"{}\" fromY=\"{}\" toX=\"{}\" toY=\"{}\">\n", start.x, start.y, end.x, end.y);
			m_out << std::format("\t<color r=\"{}\" g=\"{}\" b=\"{}\" a=\"{}\">\n", color.r, color.g, color.b, color.a);
			m_out << "</line>\n";
		}

		void EndDraw()
		{
			if (!m_drawing)
			{
				throw std::logic_error("Drawing has not been started");
			}

			m_out << "</draw>" << std::endl;
			m_drawing = false;
		}

	private:
		std::ostream& m_out;
		bool m_drawing = false;
	};
}
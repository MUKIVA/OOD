#pragma once
#include <iostream>
#include <cstdint>
#include <iomanip>

// ������������ ���� ����������� ���������� (���������� ��� ���������)
namespace graphics_lib
{
	// ����� ��� ���������
	class ICanvas
	{
	public:
		virtual void SetColor(std::uint32_t rgbColor) = 0;
		// ������ "����" � ����� x, y
		virtual void MoveTo(int x, int y) = 0;
		// ������ ����� � ������� �������, ���������� ���� � ����� x,y
		virtual void LineTo(int x, int y) = 0;
		virtual ~ICanvas() = default;
	};

	// ���������� ������ ��� ���������
	class CCanvas : public ICanvas
	{
	public:
		void SetColor(std::uint32_t rgbColor) override
		{
			std::cout << "SetColor ( #" << std::hex 
				<< std::setw(2) << std::setfill('0') << (std::uint32_t)((rgbColor >> 16) & 0xff) 
				<< std::setw(2) << std::setfill('0') << (std::uint32_t)((rgbColor >> 8) & 0xff) 
				<< std::setw(2) << std::setfill('0') << (std::uint32_t)((rgbColor >> 0) & 0xff)
				<< " )\n";
		}

		void MoveTo(int x, int y) override
		{
			std::cout << std::dec << "MoveTo (" << x << ", " << y << ")\n";
		}

		void LineTo(int x, int y) override
		{
			std::cout << std::dec << "LineTo (" << x << ", " << y << ")\n";
		}

	};	
}
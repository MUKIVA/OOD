#pragma once
#include <cstdint>

template<typename T>
struct Point
{
	T x;
	T y;
};

template<typename T>
struct Rect
{
	Point<T> topLeft;
	T width;
	T height;
};

typedef Rect<double> RectD;
typedef std::uint32_t RGBAColor;
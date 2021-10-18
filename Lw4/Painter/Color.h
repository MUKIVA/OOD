#pragma once

#include <map>
#include <string>

enum class Color
{
	RED,
	GREEN,
	BLUE,
	PINK,
	YELLOW,
	BLACK
};

const std::map<Color, std::string> COLOR_TO_STRING = {
	{ Color::RED, "red" },
	{ Color::GREEN, "green" },
	{ Color::BLUE, "blue" },
	{ Color::PINK, "pink" },
	{ Color::YELLOW, "yellow" },
	{ Color::BLACK, "black" }
};

const std::map<std::string, Color> STRING_TO_COLOR = {
	{ "red", Color::RED },
	{ "green", Color::GREEN },
	{ "blue", Color::BLUE },
	{ "pink", Color::PINK },
	{ "yellow", Color::YELLOW },
	{ "black", Color::BLACK }
};
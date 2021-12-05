#pragma once

class RGBAColor
{
public:
	RGBAColor(float r, float g, float b, float a): r(r), g(g), b(b), a(a) {}

	float r;
	float g;
	float b;
	float a;
};


class CStyle
{
public:
	bool IsEnable() const;
	void Enable(bool enable);

	RGBAColor GetColor() const;
	void SetColor(RGBAColor color);
};

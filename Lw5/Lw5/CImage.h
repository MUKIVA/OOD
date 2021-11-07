#pragma once

#include "IImage.h"

class CImage : public IImage
{
public:
	Path GetPath() const override
	{
		return m_path;
	}

	int GetWidth() const override
	{
		return m_width;
	}

	int GetHeight() const override
	{
		return m_height;
	}

	void Resize(int width, int height) override
	{
		m_height = height;
		m_width = width;
	}

private:
	Path m_path;
	int m_width = 0;
	int m_height = 0;
};
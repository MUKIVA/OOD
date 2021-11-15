#pragma once

#include "IImage.h"

const int MAX_IMAGE_SIZE = 10000;
const int MIN_IMAGE_SIZE = 1;

class CImage : public IImage
{
public:
	CImage(int width, int height, Path path)
		: m_height(height)
		, m_width(width)
		, m_path(path)
	{
	}

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
		if ((width > MAX_IMAGE_SIZE || width < MIN_IMAGE_SIZE)
			|| (height > MAX_IMAGE_SIZE || height < MIN_IMAGE_SIZE))
			throw std::invalid_argument("Invalid image size");

		m_height = height;
		m_width = width;
	}

private:
	Path m_path;
	int m_width = 0;
	int m_height = 0;
};
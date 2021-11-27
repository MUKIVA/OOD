#include "CSlide.h"

CSlide::CSlide(size_t width, size_t height)
	: m_width(width)
	, m_height(height)
{
}

size_t CSlide::GetWidth() const
{
	return m_width;
}

size_t CSlide::GetHeight() const
{
	return m_height;
}

void CSlide::ResizeSlide(size_t width, size_t height)
{
	m_width = width;
	m_height = height;
}

size_t CSlide::GetShapeCount() const
{
	return m_shapes.size();
}

void CSlide::InsertShape(std::shared_ptr<IShape> const& shape, size_t position)
{
	if (position >= GetShapeCount())
	{
		m_shapes.push_back(shape);
	}
	else
	{
		m_shapes.emplace(m_shapes.begin() + position, shape);
	}

}

std::shared_ptr<IShape> CSlide::GetShapeAtIndex(size_t index)
{
	if (index >= GetShapeCount())
		throw std::out_of_range("Index is out of range");

	return m_shapes.at(index);
}

void CSlide::RemoveShapeAtIndex(size_t index)
{
	if (index >= GetShapeCount())
		throw std::out_of_range("Index is out of range");

	m_shapes.erase(m_shapes.begin() + index);
}

void CSlide::Draw(ICanvas& canvas)
{
	for (auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}



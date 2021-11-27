#pragma once
#include "ISlide.h"
#include "CGroupShape.h"
#include <vector>

class CSlide : public ISlide
{
public:

	CSlide(size_t width, size_t height);

	size_t GetWidth() const override;
	size_t GetHeight() const override;

	void ResizeSlide(size_t width, size_t height) override;

	size_t GetShapeCount() const override;
	void InsertShape(std::shared_ptr<IShape> const& shape, size_t position = std::numeric_limits<size_t>::max()) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;

	void Draw(ICanvas& canvas) override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	size_t m_width;
	size_t m_height;
};

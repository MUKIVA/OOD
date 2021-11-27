#pragma once
#include "IShape.h"

class IShapes
{
public:
	virtual size_t GetShapeCount() const = 0;
	virtual void InsertShape(std::shared_ptr<IShape> const& shape, size_t position = std::numeric_limits<size_t>::max()) = 0;
	virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;

	virtual ~IShapes() = default;
};
#pragma once

#include <vector>
#include <memory>
#include "CShape.h"

class CPictureDraft
{
public:
	size_t GetShapeCount() const
	{
		return m_shapes.size();
	}

	const std::unique_ptr<CShape>& GetShape(size_t index) const
	{
		return m_shapes.at(index);
	}

	void InsertShape(std::unique_ptr<CShape>&& shape)
	{
		m_shapes.push_back(std::move(shape));
	}

private:
	std::vector<std::unique_ptr<CShape>> m_shapes;
};
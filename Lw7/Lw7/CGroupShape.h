#pragma once
#include "IGroupShape.h"
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>


class CGroupShape : public IGroupShape, std::enable_shared_from_this<CGroupShape>
{
public:

	CGroupShape(std::vector<std::shared_ptr<IShape>>& shapes)
		: m_shapes(shapes)
	{
	}

	RectD GetFrame() const;
	void SetFrame(const RectD& rect);

	std::shared_ptr<IOutlineStyle> GetOutlineStyle();
	const std::shared_ptr<IOutlineStyle> GetOutlineStyle() const;

	std::shared_ptr<IFillStyle> GetFillStyle();
	const std::shared_ptr<IFillStyle> GetFillStyle() const;

	std::shared_ptr<IGroupShape> GetGroup();
	std::shared_ptr<const IGroupShape> GetGroup() const;

	std::shared_ptr<IGroupShape> GetParent();
	std::shared_ptr<const IGroupShape> GetParent() const;
	void SetParent(std::shared_ptr<IGroupShape> parent);

	size_t GetShapeCount() const;
	void InsertShape(std::shared_ptr<IShape> const& shape, size_t position = std::numeric_limits<size_t>::max());
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index);
	void RemoveShapeAtIndex(size_t index);

	void Draw(ICanvas& canvas) override;

private:
	std::shared_ptr<IOutlineStyle> m_lineStyle = nullptr;
	std::shared_ptr<IFillStyle> m_fillStyle = nullptr;
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::shared_ptr<IGroupShape> m_parent = nullptr;
};

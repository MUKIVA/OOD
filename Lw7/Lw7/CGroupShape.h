#pragma once
#include "IGroupShape.h"
#include "IFillStyleEnumerated.h"
#include "IOutlineStyleEnumerated.h"
#include "CGroupOutlineStyle.h"
#include "CGroupFillStyle.h"
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>


class CGroupShape 
	: public IGroupShape
	, public std::enable_shared_from_this<CGroupShape>
{
public:

	CGroupShape(std::vector<std::shared_ptr<IShape>>& shapes);

	CGroupShape(std::shared_ptr<IShape>& oneShape, std::shared_ptr<IShape>& twoShape);

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

	// Унаследовано через IFillStyleEnumerated
	virtual void EnumerateFillStyles(const std::function<void(IFillStyle& style)>& callback) const override;

	// Унаследовано через IOutlineStyleEnumerated
	virtual void EnumerateOutlineStyles(const std::function<void(IOutlineStyle& style)>& callback) const override;

	void Draw(ICanvas& canvas) override;

	~CGroupShape();

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::shared_ptr<IGroupShape> m_parent = nullptr;
	
	bool IsParent(std::shared_ptr<IShape> parent);
	
	void MoveShapes(double widthRatio, double heightRatio, double leftOffset, double topOffset);

	
};

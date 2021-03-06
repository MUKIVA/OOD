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

	//CGroupShape(const std::vector<std::shared_ptr<IShape>>& shapes);

	//CGroupShape(const std::shared_ptr<IShape>& oneShape, const std::shared_ptr<IShape>& twoShape);

	std::optional<RectD> GetFrame() const;
	void SetFrame(const RectD& rect);

	std::weak_ptr<IOutlineStyle> GetOutlineStyle();
	const std::weak_ptr<IOutlineStyle> GetOutlineStyle() const;

	std::weak_ptr<IFillStyle> GetFillStyle();
	const std::weak_ptr<IFillStyle> GetFillStyle() const;

	std::shared_ptr<IGroupShape> GetGroup();
	std::shared_ptr<const IGroupShape> GetGroup() const;

	std::weak_ptr<IGroupShape> GetParent();
	std::weak_ptr<const IGroupShape> GetParent() const;
	void SetParent(std::shared_ptr<IGroupShape> parent);

	size_t GetShapeCount() const;
	void InsertShape(std::shared_ptr<IShape> const& shape, size_t position = std::numeric_limits<size_t>::max());
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index);
	void RemoveShapeAtIndex(size_t index);

	// ???????????? ????? IFillStyleEnumerated
	virtual void EnumerateFillStyles(const std::function<void(IFillStyle& style)>& callback) const override;

	// ???????????? ????? IOutlineStyleEnumerated
	virtual void EnumerateOutlineStyles(const std::function<void(IOutlineStyle& style)>& callback) const override;

	void Draw(ICanvas& canvas) override;

	~CGroupShape();

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::weak_ptr<IGroupShape> m_parent;
	std::shared_ptr<IOutlineStyle> m_lineStyle = nullptr; //std::make_unique<CGroupOutlineStyle>();
	std::shared_ptr<IFillStyle> m_fillStyle = nullptr; //std::make_unique<CGroupFillStyle>();
	
	bool IsParent(std::shared_ptr<IShape> parent);
	
	void MoveShapes(double widthRatio, double heightRatio, double leftOffset, double topOffset);

	
};

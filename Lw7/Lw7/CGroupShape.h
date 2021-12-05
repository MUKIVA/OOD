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

	std::optional<RectD> GetFrame() const override;
	void SetFrame(const RectD& rect) override;

	std::unique_ptr<IOutlineStyle> GetOutlineStyle() override;
	const std::unique_ptr<IOutlineStyle> GetOutlineStyle() const override;
	void SetOutlineStyle(const IOutlineStyle& style) override;

	std::unique_ptr<IFillStyle> GetFillStyle() override;
	const std::unique_ptr<IFillStyle> GetFillStyle() const override;
	void SetFillStyle(const IFillStyle& style) override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	std::weak_ptr<IGroupShape> GetParent() override;
	std::weak_ptr<const IGroupShape> GetParent() const override;
	void SetParent(std::shared_ptr<IGroupShape> parent) override;

	size_t GetShapeCount() const override;
	void InsertShape(std::shared_ptr<IShape> const& shape, size_t position = std::numeric_limits<size_t>::max()) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;

	// Унаследовано через IFillStyleEnumerated
	virtual void EnumerateFillStyles(const std::function<void(IFillStyle& style)>& callback) const override;

	// Унаследовано через IOutlineStyleEnumerated
	virtual void EnumerateOutlineStyles(const std::function<void(IOutlineStyle& style)>& callback) const override;

	void Draw(ICanvas& canvas) override;

	~CGroupShape();

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::weak_ptr<IGroupShape> m_parent;
	//std::unique_ptr<IOutlineStyle> m_lineStyle = nullptr; //std::make_unique<CGroupOutlineStyle>();
	//std::unique_ptr<IFillStyle> m_fillStyle = nullptr; //std::make_unique<CGroupFillStyle>();
	
	bool IsParent(std::shared_ptr<IShape> parent);
	
	void MoveShapes(double widthRatio, double heightRatio, double leftOffset, double topOffset);

	
};

#pragma once
#include "IDrawable.h"
#include "CommonTypes.h"
#include "COutlineStyle.h"
#include "CFillStyle.h"
#include <memory>

class IGroupShape;

class IShape : public IDrawable
{
public:
	virtual std::optional<RectD> GetFrame() const = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual std::weak_ptr<IOutlineStyle> GetOutlineStyle() = 0;
	virtual const std::weak_ptr<IOutlineStyle> GetOutlineStyle() const = 0;

	virtual std::weak_ptr<IFillStyle> GetFillStyle() = 0;
	virtual const std::weak_ptr<IFillStyle> GetFillStyle() const = 0;

	virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
	virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

	virtual std::weak_ptr<IGroupShape> GetParent() = 0;
	virtual std::weak_ptr<const IGroupShape> GetParent() const = 0;
	virtual void SetParent(std::shared_ptr<IGroupShape> parent) = 0;

	virtual ~IShape() = default;
};

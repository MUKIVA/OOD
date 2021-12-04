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
	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual IOutlineStyle& GetOutlineStyle() = 0;
	virtual const IOutlineStyle& GetOutlineStyle() const = 0;

	virtual IFillStyle& GetFillStyle() = 0;
	virtual const IFillStyle& GetFillStyle() const = 0;

	virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
	virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

	virtual std::shared_ptr<IGroupShape> GetParent() = 0;
	virtual std::shared_ptr<const IGroupShape> GetParent() const = 0;
	virtual void SetParent(std::shared_ptr<IGroupShape> parent) = 0;

	virtual ~IShape() = default;
};

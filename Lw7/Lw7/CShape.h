#pragma once
#include "IShape.h"
#include "CFillStyle.h"
#include "COutlineStyle.h"
#include "IOutlineStyle.h"
#include "IFillStyle.h"
#include "IGroupShape.h"


class CShape : public IShape
{
public:

	std::optional<RectD> GetFrame() const override;
	void SetFrame(const RectD& rect);

	std::unique_ptr<IOutlineStyle> GetOutlineStyle() override;
	const std::unique_ptr<IOutlineStyle> GetOutlineStyle() const override;
	void SetOutlineStyle(const IOutlineStyle& style) override;

	std::unique_ptr<IFillStyle> GetFillStyle() override;
	const std::unique_ptr<IFillStyle> GetFillStyle() const override;
	virtual void SetFillStyle(const IFillStyle& style) override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	std::weak_ptr<IGroupShape> GetParent();
	std::weak_ptr<const IGroupShape> GetParent() const;
	void SetParent(std::shared_ptr<IGroupShape> parent);

	virtual void MovePoints(double offsetX, double offsetY, double ratioWidth, double ratioHeight) = 0;

	~CShape();

protected:
	std::shared_ptr<RectD> m_frame = nullptr;

private:
	std::unique_ptr<IOutlineStyle> m_outlineStyle = std::make_unique<COutlineStyle>();
	std::unique_ptr<IFillStyle> m_fillStyle = std::make_unique<CFillStyle>();

	std::weak_ptr<IGroupShape> m_parent;
};

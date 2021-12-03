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

	RectD GetFrame() const override;
	void SetFrame(const RectD& rect);

	std::shared_ptr<IOutlineStyle> GetOutlineStyle() override;
	const std::shared_ptr<IOutlineStyle> GetOutlineStyle() const override;

	std::shared_ptr<IFillStyle> GetFillStyle() override;
	const std::shared_ptr<IFillStyle> GetFillStyle() const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	std::shared_ptr<IGroupShape> GetParent();
	std::shared_ptr<const IGroupShape> GetParent() const;
	void SetParent(std::shared_ptr<IGroupShape> parent);

	virtual void MovePoints(double offsetX, double offsetY, double ratioWidth, double ratioHeight) = 0;

	~CShape();

protected:
	std::shared_ptr<RectD> m_frame = nullptr;

private:
	std::shared_ptr<IOutlineStyle> m_outlineStyle = std::make_shared<COutlineStyle>();
	std::shared_ptr<IFillStyle> m_fillStyle = std::make_shared<CFillStyle>();
	std::shared_ptr<IGroupShape> m_parent = nullptr;
};

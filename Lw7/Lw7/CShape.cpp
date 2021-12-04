#include "CShape.h"

std::optional<RectD> CShape::GetFrame() const
{
	if (m_frame == nullptr)
		return std::nullopt;

	return *m_frame;
}

void CShape::SetFrame(const RectD& rect)
{
	
	if (m_frame != nullptr)
	{
		double offsetX = rect.topLeft.x - (*m_frame).topLeft.x;
		double offsetY = rect.topLeft.y - (*m_frame).topLeft.y;
		double ratioWidth = rect.width / (*m_frame).width;
		double ratioHeight = rect.height / (*m_frame).height;
		MovePoints(offsetX, offsetY, ratioWidth, ratioHeight);
	}
	m_frame = std::make_shared<RectD>(rect);
}

std::weak_ptr<IOutlineStyle> CShape::GetOutlineStyle()
{
	return m_outlineStyle;
}

const std::weak_ptr<IOutlineStyle> CShape::GetOutlineStyle() const
{
	return m_outlineStyle;
}

std::weak_ptr<IFillStyle> CShape::GetFillStyle()
{
	return m_fillStyle;
}

const std::weak_ptr<IFillStyle> CShape::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IGroupShape> CShape::GetGroup()
{
	return nullptr;
}

std::shared_ptr<const IGroupShape> CShape::GetGroup() const
{
	return nullptr;
}

std::weak_ptr<IGroupShape> CShape::GetParent()
{
	return m_parent;
}

std::weak_ptr<const IGroupShape> CShape::GetParent() const
{
	return GetParent();
}

void CShape::SetParent(std::shared_ptr<IGroupShape> parent)
{
	m_parent = parent;
}

CShape::~CShape()
{
	if (!m_parent.expired())
	{
		std::shared_ptr<IShape> sharedThis(this);
		auto lock = m_parent.lock();
		for (int i = 0; i < lock->GetShapeCount(); ++i)
		{
			if ( sharedThis == lock->GetShapeAtIndex(i))
			{
				lock->RemoveShapeAtIndex(i);
			}
		}
	}
}


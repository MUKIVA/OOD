#include "CShape.h"

RectD CShape::GetFrame() const
{
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

std::shared_ptr<IOutlineStyle> CShape::GetOutlineStyle()
{
	return m_outlineStyle;
}

const std::shared_ptr<IOutlineStyle> CShape::GetOutlineStyle() const
{
	return m_outlineStyle;
}

std::shared_ptr<IFillStyle> CShape::GetFillStyle()
{
	return m_fillStyle;
}

const std::shared_ptr<IFillStyle> CShape::GetFillStyle() const
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

std::shared_ptr<IGroupShape> CShape::GetParent()
{
	return m_parent;
}

std::shared_ptr<const IGroupShape> CShape::GetParent() const
{
	return m_parent;
}

void CShape::SetParent(std::shared_ptr<IGroupShape> parent)
{
	m_parent = parent;
}

CShape::~CShape()
{
	if (m_parent != nullptr)
	{
		std::shared_ptr<IShape> sharedThis(this);
		for (int i = 0; i < m_parent->GetShapeCount(); ++i)
		{
			if ( sharedThis == m_parent->GetShapeAtIndex(i))
			{
				m_parent->RemoveShapeAtIndex(i);
			}
		}
	}
}


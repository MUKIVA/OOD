#include "CGroupShape.h"
#include "CGroupOutlineStyle.h"
#include "CGroupFillStyle.h"

size_t CGroupShape::GetShapeCount() const
{
	return m_shapes.size();
}

void CGroupShape::InsertShape(std::shared_ptr<IShape> const& shape, size_t position)
{
	if (IsParent(shape))
		throw std::logic_error("Cannot recursive insert");

	if (position >= GetShapeCount())
	{
		m_shapes.push_back(shape);
	}
	else
	{
		m_shapes.emplace(m_shapes.begin() + position, shape);
	}
	shape->SetParent(GetGroup());
}

std::shared_ptr<IShape> CGroupShape::GetShapeAtIndex(size_t index)
{
	if (index >= GetShapeCount())
		throw std::out_of_range("Index is out of range");

	return m_shapes.at(index);
}

void CGroupShape::RemoveShapeAtIndex(size_t index)
{
	if (index >= GetShapeCount())
		throw std::out_of_range("Index is out of range");

	if (GetShapeCount() == 1)
		throw std::logic_error("You cannot delete the last item from the group");

	m_shapes.erase(m_shapes.begin() + index);
}

void CGroupShape::Draw(ICanvas& canvas)
{
	for (auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

CGroupShape::~CGroupShape()
{
	if (m_parent != nullptr)
	{
		size_t parentShapeCount = m_parent->GetShapeCount();
		for (int i = 0; i < parentShapeCount; ++i)
		{
			if (GetGroup() == m_parent->GetShapeAtIndex(i))
			{
				m_parent->RemoveShapeAtIndex(i);
			}
		}
	}
}

CGroupShape::CGroupShape(const std::vector<std::shared_ptr<IShape>>& shapes)
	: m_shapes(shapes)
{
	if (shapes.size() < 2)
		throw std::logic_error("A group cannot contain less than two elements");
}

CGroupShape::CGroupShape(const std::shared_ptr<IShape>& oneShape, const std::shared_ptr<IShape>& twoShape)
{
	m_shapes.push_back(oneShape);
	m_shapes.push_back(twoShape);
}

RectD CGroupShape::GetFrame() const
{
	std::vector<double> topCoords;
	std::vector<double> leftCoords;
	std::vector<double> rightCoords;
	std::vector<double> bottomCoords;

	for (auto& shape : m_shapes)
	{
		RectD shapeFrame = shape->GetFrame();
		topCoords.push_back(shapeFrame.topLeft.y);
		leftCoords.push_back(shapeFrame.topLeft.x);
		bottomCoords.push_back(shapeFrame.topLeft.y + shapeFrame.height);
		rightCoords.push_back(shapeFrame.topLeft.x + shapeFrame.width);
	}

	double left = *std::min_element(leftCoords.begin(), leftCoords.end());
	double top = *std::min_element(topCoords.begin(), topCoords.end());
	double right = *std::max_element(rightCoords.begin(), rightCoords.end());
	double bottom = *std::max_element(bottomCoords.begin(), bottomCoords.end());

	RectD rect = {
		{ left, top },
		right - left,
		bottom - top,
	};

	return rect;
}

bool CGroupShape::IsParent(std::shared_ptr<IShape> parent)
{
	auto currentNode = GetGroup();
	while (currentNode != nullptr)
	{
		if (currentNode == parent)
			return true;
		currentNode = currentNode->GetParent();
	}
	return false;
}

void CGroupShape::MoveShapes(double widthRatio, double heightRatio, double leftOffset, double topOffset)
{
	for (auto& shape : m_shapes)
	{
		auto shapeFrame = shape->GetFrame();
		auto newFrame = RectD{
			widthRatio * (shapeFrame.topLeft.x + leftOffset),
			heightRatio * (shapeFrame.topLeft.y + topOffset),
			shapeFrame.width * widthRatio,
			shapeFrame.height * heightRatio
		};
		shape->SetFrame(newFrame);
	}
}

void CGroupShape::EnumerateFillStyles(const std::function<void(IFillStyle& style)>& callback) const
{
	for (auto& shape : m_shapes)
	{
		callback(shape->GetFillStyle());
	}
}

void CGroupShape::EnumerateOutlineStyles(const std::function<void(IOutlineStyle& style)>& callback) const
{
	for (auto& shape : m_shapes)
	{
		callback(shape->GetOutlineStyle());
	}
}

void CGroupShape::SetFrame(const RectD& rect)
{
	auto oldFrame = GetFrame();
	auto widthRatio = rect.width / oldFrame.width;
	auto heightRatio = rect.height / oldFrame.height;
	auto leftOffset = rect.topLeft.x - oldFrame.topLeft.x;
	auto topOffset = rect.topLeft.y - oldFrame.topLeft.y;

	MoveShapes(widthRatio, heightRatio, leftOffset, topOffset);

	oldFrame = GetFrame();
	leftOffset = rect.topLeft.x - oldFrame.topLeft.x;
	topOffset = rect.topLeft.y - oldFrame.topLeft.y;
	
	MoveShapes(1, 1, leftOffset, topOffset);
}

IOutlineStyle& CGroupShape::GetOutlineStyle()
{
	if (m_lineStyle == nullptr)
		m_lineStyle = std::make_unique<CGroupOutlineStyle>(GetGroup());

	return *m_lineStyle;
}

const IOutlineStyle& CGroupShape::GetOutlineStyle() const
{
	return GetOutlineStyle();
}

IFillStyle& CGroupShape::GetFillStyle()
{
	if (m_fillStyle == nullptr)
		m_fillStyle = std::make_unique<CGroupFillStyle>(GetGroup());

	return *m_fillStyle;
}

const IFillStyle& CGroupShape::GetFillStyle() const
{
	return GetFillStyle();
}

std::shared_ptr<IGroupShape> CGroupShape::GetGroup()
{
	return shared_from_this();
}

std::shared_ptr<const IGroupShape> CGroupShape::GetGroup() const
{
	return GetGroup();
}

std::shared_ptr<IGroupShape> CGroupShape::GetParent()
{
	return m_parent;
}

std::shared_ptr<const IGroupShape> CGroupShape::GetParent() const
{
	return m_parent;
}

void CGroupShape::SetParent(std::shared_ptr<IGroupShape> parent)
{
	m_parent = parent;
}


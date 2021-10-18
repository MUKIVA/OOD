#pragma once

#include "IShapeFactory.h"
#include <sstream>
#include "CElipse.h"
#include "CRectangle.h"
#include "CRegularPolygon.h"
#include "CTriangle.h"

const std::string RECTANGLE_NAME = "rectangle";
const std::string TRIANGLE_NAME = "triangle";
const std::string ELLIPSE_NAME = "ellipse";
const std::string POLYGON_NAME = "polygon";

class CShapeFactory : public IShapeFactory
{
public:
	std::unique_ptr<CShape> CreateShape(std::string const& description) override
	{
		std::istringstream iss(description);
		std::string shapeName;
		iss >> shapeName;
		std::string colorName;
		iss >> colorName;
		Color color;
		try
		{
			 color = STRING_TO_COLOR.at(colorName);
		}
		catch (...)
		{
			throw std::invalid_argument("Invalid color name");
		}

		if (shapeName == RECTANGLE_NAME) return CreateRectangle(iss, color);
		if (shapeName == TRIANGLE_NAME) return CreateTriangle(iss, color);
		if (shapeName == ELLIPSE_NAME) return CreateEllipse(iss, color);
		if (shapeName == POLYGON_NAME) return CreateRegularPolygon(iss, color);

		throw std::invalid_argument("Invalid shape name");
	}

private:
	std::unique_ptr<CShape> CreateTriangle(std::istream& is, Color color) const
	{
		return std::make_unique<CTriangle>(GetPoint(is), GetPoint(is), GetPoint(is), color);
	}
	std::unique_ptr<CShape> CreateEllipse(std::istream& is, Color color) const
	{
		Point center = GetPoint(is);
		double width, heght;
		is >> width >> heght;
		return std::make_unique<CElipse>(color, heght, width, center);
	}
	std::unique_ptr<CShape> CreateRectangle(std::istream& is, Color color) const
	{
		return std::make_unique<CRectangle>(GetPoint(is), GetPoint(is), color);
	}
	std::unique_ptr<CShape> CreateRegularPolygon(std::istream& is, Color color) const
	{
		Point center = GetPoint(is);
		unsigned int vertexCount;
		double radius;
		is >> vertexCount >> radius;
		return std::make_unique<CRegularPolygon>(center, vertexCount, radius, color);
	}

	Point GetPoint(std::istream& is) const
	{
		Point p;
		double x, y;
		is >> x >> y;
		p = { x, y };
		return p;
	}
};
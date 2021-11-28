#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"

#include "../Lw7/CCanvas.h"
#include "../Lw7/CEllipse.h"
#include "../Lw7/CFillStyle.h"
#include "../Lw7/CGroupFillStyle.h"
#include "../Lw7/CGroupOutlineStyle.h"
#include "../Lw7/CGroupShape.h"
#include "../Lw7/CommonTypes.h"
#include "../Lw7/COutlineStyle.h"
#include "../Lw7/CRectangle.h"
#include "../Lw7/CShape.h"
#include "../Lw7/CSlide.h"
#include "../Lw7/CTriangle.h"

#include <iostream>
#include <sstream>


using namespace std;

Point<double> const MakeConstDPoint(double x, double y)
{
	return Point<double>{ x, y };
}

bool ValidShape(shared_ptr<IShape>& shape, RectD rect, RGBAColor lineColor, RGBAColor fillColor, double lineWidth)
{
	bool result = true;
	auto fr = shape->GetFrame();
	result = (result) ? shape->GetFillStyle()->GetColor() == fillColor : false;
	result = (result) ? shape->GetOutlineStyle()->GetColor() == lineColor : false;
	result = (result) ? shape->GetOutlineStyle()->GetLineWidth() == lineWidth : false;
	result = (result) ? abs(shape->GetFrame().topLeft.x - rect.topLeft.x) < 0.001 : false;
	result = (result) ? abs(shape->GetFrame().topLeft.y - rect.topLeft.y) < 0.001 : false;
	result = (result) ? abs(shape->GetFrame().height - rect.height ) < 0.001 : false;
	result = (result) ? abs(shape->GetFrame().width - rect.width) < 0.001 : false;
	return result;
}

bool ValidFrame(RectD rect, double topLeftX, double topLeftY, double width, double height)
{
	bool result = true;

	result = (result) ? rect.topLeft.x == topLeftX : false;
	result = (result) ? rect.topLeft.y == topLeftY : false;
	result = (result) ? rect.width == width : false;
	result = (result) ? rect.height == height : false;

	return result;
}

SCENARIO("Test full group creation")
{
	shared_ptr<IShape> neck = make_shared<CRectangle>(MakeConstDPoint(200, 500), MakeConstDPoint(300, 700));
	neck->GetFillStyle()->SetColor(0xDDBDA2);
	shared_ptr<IShape> face = make_shared<CEllipse>(MakeConstDPoint(250, 500), 100, 100);
	face->GetFillStyle()->SetColor(0xFFDFC4);
	shared_ptr<IShape> eyeLeft = make_shared<CEllipse>(MakeConstDPoint(200, 450), 30, 10);
	eyeLeft->GetFillStyle()->SetColor(0xFFFFFF);
	shared_ptr<IShape> eyeRight = make_shared<CEllipse>(MakeConstDPoint(300, 450), 30, 10);
	eyeRight->GetFillStyle()->SetColor(0xFFFFFF);
	shared_ptr<IShape> mouth = make_shared<CTriangle>(MakeConstDPoint(250, 500), MakeConstDPoint(240, 510), MakeConstDPoint(260, 510));
	mouth->GetFillStyle()->SetColor(0xF44464);
	mouth->GetOutlineStyle()->SetColor(0x900000);

	shared_ptr<IGroupShape> faceGroup = make_shared<CGroupShape>();

	faceGroup->InsertShape(neck);
	faceGroup->InsertShape(face);
	faceGroup->InsertShape(eyeLeft);
	faceGroup->InsertShape(eyeRight);
	faceGroup->InsertShape(mouth);

	auto el0 = faceGroup->GetShapeAtIndex(0);
	auto el1 = faceGroup->GetShapeAtIndex(1);
	auto el2 = faceGroup->GetShapeAtIndex(2);
	auto el3 = faceGroup->GetShapeAtIndex(3);
	auto el4 = faceGroup->GetShapeAtIndex(4);

	REQUIRE(ValidShape(el0, { { 200, 500 }, 100, 200 }, 0x000000, 0xDDBDA2, 5));
	REQUIRE(ValidShape(el1, { { 150, 400 }, 200, 200 }, 0x000000, 0xFFDFC4, 5));
	REQUIRE(ValidShape(el2, { { 170, 440 }, 60, 20 }, 0x000000, 0xFFFFFF, 5));
	REQUIRE(ValidShape(el3, { { 270, 440 }, 60, 20 }, 0x000000, 0xFFFFFF, 5));
	REQUIRE(ValidShape(el4, { { 240, 500 }, 20, 10 }, 0x900000, 0xF44464, 5));

	WHEN("Group frame resize")
	{
		faceGroup->SetFrame({ { 150, 400 }, 100, 200 });
		RectD groupRect = faceGroup->GetFrame();
		REQUIRE(ValidFrame(groupRect, 150, 400, 100, 200));

		REQUIRE(ValidShape(el0, { { 175, 466.666 }, 50, 133.334 }, 0x000000, 0xDDBDA2, 5));
		REQUIRE(ValidShape(el1, { { 150, 400 }, 100, 133.333 }, 0x000000, 0xFFDFC4, 5));
		REQUIRE(ValidShape(el2, { { 160, 426.666 }, 30, 13.333 }, 0x000000, 0xFFFFFF, 5));
		REQUIRE(ValidShape(el3, { { 210, 426.666 }, 30, 13.333 }, 0x000000, 0xFFFFFF, 5));
		REQUIRE(ValidShape(el4, { { 195, 466.666 }, 10, 6.666 }, 0x900000, 0xF44464, 5));
	}

	WHEN("Group change color")
	{
		faceGroup->GetOutlineStyle()->SetColor(0xDDDDDD);

		REQUIRE(ValidShape(el0, { { 200, 500 }, 100, 200 }, 0xDDDDDD, 0xDDBDA2, 5));
		REQUIRE(ValidShape(el1, { { 150, 400 }, 200, 200 }, 0xDDDDDD, 0xFFDFC4, 5));
		REQUIRE(ValidShape(el2, { { 170, 440 }, 60, 20 }, 0xDDDDDD, 0xFFFFFF, 5));
		REQUIRE(ValidShape(el3, { { 270, 440 }, 60, 20 }, 0xDDDDDD, 0xFFFFFF, 5));
		REQUIRE(ValidShape(el4, { { 240, 500 }, 20, 10 }, 0xDDDDDD, 0xF44464, 5));

		faceGroup->GetFillStyle()->SetColor(0xDDDDDD);

		REQUIRE(ValidShape(el0, { { 200, 500 }, 100, 200 }, 0xDDDDDD, 0xDDDDDD, 5));
		REQUIRE(ValidShape(el1, { { 150, 400 }, 200, 200 }, 0xDDDDDD, 0xDDDDDD, 5));
		REQUIRE(ValidShape(el2, { { 170, 440 }, 60, 20 }, 0xDDDDDD, 0xDDDDDD, 5));
		REQUIRE(ValidShape(el3, { { 270, 440 }, 60, 20 }, 0xDDDDDD, 0xDDDDDD, 5));
		REQUIRE(ValidShape(el4, { { 240, 500 }, 20, 10 }, 0xDDDDDD, 0xDDDDDD, 5));
	}

	WHEN("GetColor with different colors in group")
	{
		REQUIRE(faceGroup->GetFillStyle()->GetColor() == nullopt);
		REQUIRE(faceGroup->GetOutlineStyle()->GetColor() == nullopt);
	}

	WHEN("GetLineWidth")
	{
		REQUIRE(faceGroup->GetOutlineStyle()->GetLineWidth() == 5);
	}
}

SCENARIO("test recursive insertion")
{
	shared_ptr<IShape> figure1 = make_shared<CRectangle>(MakeConstDPoint(200, 500), MakeConstDPoint(300, 700));
	shared_ptr<IShape> figure2 = make_shared<CRectangle>(MakeConstDPoint(200, 500), MakeConstDPoint(300, 700));
	shared_ptr<IShape> figure3 = make_shared<CRectangle>(MakeConstDPoint(200, 500), MakeConstDPoint(300, 700));
	shared_ptr<IShape> figure4 = make_shared<CRectangle>(MakeConstDPoint(200, 500), MakeConstDPoint(300, 700));
	shared_ptr<IShape> figure5 = make_shared<CRectangle>(MakeConstDPoint(200, 500), MakeConstDPoint(300, 700));
	shared_ptr<IShape> figure6 = make_shared<CRectangle>(MakeConstDPoint(200, 500), MakeConstDPoint(300, 700));
	shared_ptr<IGroupShape> group1 = make_shared<CGroupShape>();
	shared_ptr<IGroupShape> group2 = make_shared<CGroupShape>();
	shared_ptr<IGroupShape> group3 = make_shared<CGroupShape>();
	REQUIRE_NOTHROW(group1->InsertShape(group2));
	REQUIRE_NOTHROW(group2->InsertShape(group3));
	REQUIRE_THROWS(group3->InsertShape(group1));
}

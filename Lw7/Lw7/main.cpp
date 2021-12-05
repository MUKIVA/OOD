#include <iostream>
#include <fstream>
#include <memory>
#include "CommonTypes.h"
#include "CGroupOutlineStyle.h"
#include "CSlide.h"
#include "CCanvas.h"
#include "CRectangle.h"
#include "CEllipse.h"
#include "CTriangle.h"
#include "CGroupShape.h"


using namespace std;

Point<double> const MakeConstDPoint(double x, double y)
{
	return Point<double>{ x, y };
}

int main()
{
	CSlide slide(1000, 1000);
	ofstream svg("slide.svg");
	CSvgCanvas canvas(svg);
	// ‘он
	shared_ptr<IShape> bgLeft = make_shared<CRectangle>(MakeConstDPoint(0, 0), MakeConstDPoint(500, 1000));
	bgLeft->GetOutlineStyle()->Enable(false);
	bgLeft->GetFillStyle()->SetColor(0x018786);
	shared_ptr<IShape> bgRight = make_shared<CRectangle>(MakeConstDPoint(500, 0), MakeConstDPoint(1000, 1000));
	bgRight->GetOutlineStyle()->Enable(false);
	bgRight->GetFillStyle()->SetColor(0x03DAC6);

	// Ћицо 1
	shared_ptr<IShape> face = make_shared<CEllipse>(MakeConstDPoint(250, 500), 100, 100);
	face->GetFillStyle()->SetColor(0xFFDFC4);
	shared_ptr<IShape> eyeLeft = make_shared<CEllipse>(MakeConstDPoint(200, 450), 30, 10);
	eyeLeft->GetFillStyle()->SetColor(0xFFFFFF);
	shared_ptr<IShape> eyeRight = make_shared<CEllipse>(MakeConstDPoint(300, 450), 30, 10);
	eyeRight->GetFillStyle()->SetColor(0xFFFFFF);
	shared_ptr<IShape> mouth = make_shared<CTriangle>(MakeConstDPoint(250, 500), MakeConstDPoint(240, 510), MakeConstDPoint(260, 510));
	mouth->GetFillStyle()->SetColor(0xF44464);
	mouth->GetOutlineStyle()->SetColor(0x900000);

	vector<shared_ptr<IShape>> faceOne{ face, eyeLeft, eyeRight, mouth };
	shared_ptr<IGroupShape> faceOneGroup = make_shared<CGroupShape>();
	for (auto& shape : faceOne)
	{
		faceOneGroup->InsertShape(shape);
	}

	faceOneGroup->SetFrame({ { 150, 400 }, 100, 100 });

	// Ћицо 2
	shared_ptr<IShape> face2 = make_shared<CRectangle>(MakeConstDPoint(650, 400), MakeConstDPoint(850, 600));
	face2->GetOutlineStyle()->Enable(false);
	face2->GetFillStyle()->SetColor(0xFFDFC4);
	shared_ptr<IShape> eyeLeft2 = make_shared<CRectangle>(MakeConstDPoint(700, 450), MakeConstDPoint(720, 470));
	eyeLeft2->GetOutlineStyle()->Enable(false);
	eyeLeft2->GetFillStyle()->SetColor(0xFFFFFF);
	shared_ptr<IShape> eyeLeftPupil2 = make_shared<CRectangle>(MakeConstDPoint(710, 460), MakeConstDPoint(720, 470));
	eyeLeftPupil2->GetOutlineStyle()->Enable(false);
	eyeLeftPupil2->GetFillStyle()->SetColor(0x000000);
	shared_ptr<IShape> eyeRight2 = make_shared<CRectangle>(MakeConstDPoint(780, 450), MakeConstDPoint(800, 470));
	eyeRight2->GetOutlineStyle()->Enable(false);
	eyeRight2->GetFillStyle()->SetColor(0xFFFFFF);
	shared_ptr<IShape> eyeRightPupil2 = make_shared<CRectangle>(MakeConstDPoint(790, 460), MakeConstDPoint(800, 470));
	eyeRightPupil2->GetOutlineStyle()->Enable(false);
	eyeRightPupil2->GetFillStyle()->SetColor(0x000000);
	shared_ptr<IShape> mouth2 = make_shared<CRectangle>(MakeConstDPoint(700, 550), MakeConstDPoint(800, 555));
	mouth2->GetFillStyle()->SetColor(0xF44464);
	mouth2->GetOutlineStyle()->Enable(false);


	vector<shared_ptr<IShape>> faceTwo{ face2, eyeLeft2, eyeLeftPupil2, eyeRight2, eyeRightPupil2, mouth2 };
	shared_ptr<IGroupShape> faceTwoGroup = make_shared<CGroupShape>();
	for (auto& shape : faceTwo)
	{
		faceTwoGroup->InsertShape(shape);
	}


	slide.InsertShape(bgLeft, 0);
	slide.InsertShape(bgRight, 0);
	slide.InsertShape(faceOneGroup);
	slide.InsertShape(faceTwoGroup);

	slide.Draw(canvas);

	return 0;
}

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include "CPainter.h"
#include "CPictureDraft.h"
#include "CCanvas.h"
#include "CDesigner.h"
#include "CShapeFactory.h"

using namespace std;

int main()
{

	std::ofstream pictureDatafile("resultData.svg");
	CPainter painter;
	CDesigner designer(std::make_unique<CShapeFactory>());
	CCanvas canvas(pictureDatafile);
	CPictureDraft draft = designer.CreateDraft(std::cin);

	painter.DrawPicture(draft, canvas);

	return 0;
}
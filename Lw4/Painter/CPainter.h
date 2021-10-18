#pragma once

#include "CPictureDraft.h"
#include "ICanvas.h"

class CPainter
{
public:
	void DrawPicture(CPictureDraft const& draft, ICanvas& canvas)
	{
		for (int i = 0; i < draft.GetShapeCount(); ++i)
		{
			canvas.SetColor(draft.GetShape(i)->GetColor());
			draft.GetShape(i)->Draw(canvas);
		}
	}
};
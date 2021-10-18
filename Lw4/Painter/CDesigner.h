#pragma once

#include "IDesigner.h"
#include "CPictureDraft.h"
#include "IShapeFactory.h"
#include <string>
#include <iostream>
#include <memory>

class CDesigner : public IDesigner
{
public:

	CDesigner(std::unique_ptr<IShapeFactory>&& factory)
		: m_shapeFactory(std::move(factory))
	{
	}

	CPictureDraft CreateDraft(std::istream& strm) override
	{
		CPictureDraft draft;
		std::string line;
		while (std::getline(strm, line))
		{
			try
			{
				draft.InsertShape(m_shapeFactory->CreateShape(line));
			}
			catch (const std::exception&)
			{
				continue;
			}
		}
		return draft;
	}

private:
	std::unique_ptr<IShapeFactory> m_shapeFactory;

};
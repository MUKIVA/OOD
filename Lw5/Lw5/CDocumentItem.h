#pragma once
#include <memory>
#include "IImage.h"
#include "IParagraph.h"
#include "CConstDocumentItem.h"
/*
Элемент документа. Позволяет получить доступ к изображению или параграфу
*/
class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(std::shared_ptr<IImage> image)
		: CConstDocumentItem(image)
	{
	}

	CDocumentItem(std::shared_ptr<IParagraph> paragraph)
		: CConstDocumentItem(paragraph)
	{
	}

	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<IImage> GetImage()
	{
		return m_image;
	}
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<IParagraph> GetParagraph()
	{
		return m_paragraph;
	}
};

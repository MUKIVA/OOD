#pragma once
#include <memory>
#include "IImage.h"
#include "IParagraph.h"
/*
Неизменяемый элемент документа
*/

class CConstDocumentItem
{
public:

	CConstDocumentItem(std::shared_ptr<IImage> image)
		: m_image(image)
	{
	}

	CConstDocumentItem(std::shared_ptr<IParagraph> paragraph)
		: m_paragraph(paragraph)
	{
	}

	// Возвращает указатель на константное изображение, либо nullptr,
	// если элемент не является изображением
	std::shared_ptr<const IImage> GetImage() const
	{
		return m_image;
	}
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<const IParagraph> GetParagraph() const
	{
		return m_paragraph;
	}
	virtual ~CConstDocumentItem() = default;

protected:
	std::shared_ptr<IImage> m_image = nullptr;
	std::shared_ptr<IParagraph> m_paragraph = nullptr;
};

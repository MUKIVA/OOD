#pragma once
#include <memory>
#include "IImage.h"
#include "IParagraph.h"
/*
������������ ������� ���������
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

	// ���������� ��������� �� ����������� �����������, ���� nullptr,
	// ���� ������� �� �������� ������������
	std::shared_ptr<const IImage> GetImage() const
	{
		return m_image;
	}
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<const IParagraph> GetParagraph() const
	{
		return m_paragraph;
	}
	virtual ~CConstDocumentItem() = default;

protected:
	std::shared_ptr<IImage> m_image = nullptr;
	std::shared_ptr<IParagraph> m_paragraph = nullptr;
};

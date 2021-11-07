#pragma once
#include <memory>
#include "IImage.h"
#include "IParagraph.h"
#include "CConstDocumentItem.h"
/*
������� ���������. ��������� �������� ������ � ����������� ��� ���������
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

	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	std::shared_ptr<IImage> GetImage()
	{
		return m_image;
	}
	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<IParagraph> GetParagraph()
	{
		return m_paragraph;
	}
};

#pragma once

#include "CAbstractCommand.h"
#include "IDocument.h"

class CDeleteItemCommand : public CAbstractCommand
{
public:
	CDeleteItemCommand(IDocument& document, size_t position)
		: m_document(document)
		, m_position(position)
		, m_item(document.GetItem(position))
	{
	}

protected:

	void DoExecute() override
	{
		m_document.DeleteItem(m_position);
	}

	void DoUnexecute() override
	{
		auto image = m_item.GetImage();
		auto paragraph = m_item.GetParagraph();
		if (image != nullptr)
			m_document.InsertImage(image->GetPath(), image->GetWidth(), image->GetHeight(), m_position);
		if (paragraph != nullptr)
			m_document.InsertParagraph(paragraph->GetText(), m_position);
	}

private:
	IDocument& m_document;
	size_t m_position;
	CDocumentItem m_item;
};
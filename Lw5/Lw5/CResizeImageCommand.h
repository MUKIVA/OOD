#pragma once

#include "CAbstractCommand.h"
#include "IDocument.h"

class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(IDocument& document, size_t position, int width, int height)
		: m_document(document)
		, m_newHeight(height)
		, m_newWidth(width)
		, m_position(position)
		, m_oldHeight(0)
		, m_oldWidth(0)
	{
	}

protected:

	void DoExecute() override
	{
		auto item = m_document.GetItem(*m_position).GetImage();
		if (item == nullptr)
			throw std::invalid_argument("Position is out of bounce");
		m_oldHeight = item->GetHeight();
		m_oldWidth = item->GetWidth();
		item->Resize(m_newWidth, m_newHeight);
	}

	void DoUnexecute() override
	{
		auto item = m_document.GetItem(*m_position).GetImage();
		if (item == nullptr)
			throw std::invalid_argument("Position is out of bounce");
		item->Resize(m_oldWidth, m_oldHeight);		
	}

private:
	IDocument& m_document;
	std::optional<size_t> m_position;
	int m_newWidth = 0;
	int m_newHeight = 0;
	int m_oldWidth = 0;
	int m_oldHeight = 0;
};
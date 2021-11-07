#pragma once

#include "CAbstractCommand.h"
#include "IDocument.h"

class CReplaceTextCommand : public CAbstractCommand
{
public:
	CReplaceTextCommand(IDocument& document, std::optional<size_t> position, const std::string& text)
		: m_document(document)
		, m_newText(text)
		, m_position(position)
	{
	}

protected:

	void DoExecute() override
	{
		auto item = m_document.GetItem(*m_position).GetParagraph();
		if (item == nullptr)
			throw std::invalid_argument("No paragraph with given position");
		m_oldText = item->GetText();
		item->SetText(m_newText);
	}

	void DoUnexecute() override
	{
		auto item = m_document.GetItem(*m_position).GetParagraph();
		if (item == nullptr)
			throw std::invalid_argument("No paragraph with given position");
		item->SetText(m_oldText);
	}

private:
	IDocument& m_document;
	std::string m_newText;
	std::string m_oldText;
	std::optional<size_t> m_position;
};
#pragma once

#include <optional>
#include "CAbstractCommand.h"
#include "IDocument.h"

class CInsertParagraphCommand : public CAbstractCommand
{
public:
	CInsertParagraphCommand(IDocument& document, const std::string& text, std::optional<size_t> position = std::nullopt)
		: m_document(document)
		, m_text(text)
		, m_position(position)
	{
	}

protected:
	void DoExecute() override
	{
		m_document.InsertParagraph(m_text, m_position);
	}

	void DoUnexecute() override
	{
		auto position = m_position == std::nullopt ? m_document.GetItemsCount() - 1 : *m_position;
		m_document.DeleteItem(position);
	}

private:
	IDocument& m_document;
	std::string m_text;
	std::optional<size_t> m_position = std::nullopt;
};
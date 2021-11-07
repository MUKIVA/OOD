#pragma once

#include "IDocument.h"
#include "CAbstractCommand.h"

class CSetTitleCommand : public CAbstractCommand
{
public:
	CSetTitleCommand(IDocument& document, std::istream& is)
		: m_document(document)
		, m_in(is)
	{
	}

protected:
	void DoExecute() override
	{
		m_oldTitle = m_document.GetTitle();

		if (!(m_in >> m_newTitle))
			throw std::invalid_argument("Failed to set new title");

		m_document.SetTitle(m_newTitle);
	}

	void DoUnexecute() override
	{
		m_document.SetTitle(m_oldTitle);
	}

private:
	IDocument& m_document;
	std::string m_newTitle;
	std::string m_oldTitle;
	std::istream& m_in;
};
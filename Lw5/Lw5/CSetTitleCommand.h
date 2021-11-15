#pragma once

#include "IDocument.h"
#include "CAbstractCommand.h"

class CSetTitleCommand : public CAbstractCommand
{
public:
	CSetTitleCommand(IDocument& document, std::string const& newTitle)
		: m_document(document)
		, m_newTitle(newTitle)
	{
	}

protected:
	void DoExecute() override
	{
		m_oldTitle = m_document.GetTitle();
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
};
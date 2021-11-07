#pragma once

#include "ICommand.h"
#include "IDocument.h"

class CListCommand : public ICommand
{
public:
	CListCommand(IDocument& document)
		: m_document(document)
	{
	}

	void Execute() override
	{
		m_document.ShowItems();
	}
	
	void Unexecute() override
	{
	}

private:
	IDocument& m_document;
};
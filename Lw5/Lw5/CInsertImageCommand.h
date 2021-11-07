#pragma once

#include "CAbstractCommand.h"
#include "IImage.h"
#include "IDocument.h"

class CInsertImageCommand : public CAbstractCommand
{
public:
	CInsertImageCommand(IDocument& document, const Path& path, int width, int height, std::optional<size_t> position = std::nullopt) 
		: m_document(document)
		, m_height(height)
		, m_width(width)
		, m_path(path)
		, m_position(position)
	{}

protected:
	void DoExecute() override
	{
		m_document.InsertImage(m_path, m_width, m_height, m_position);
	}
	
	void DoUnexecute() override
	{
		auto position = m_position == std::nullopt ? m_document.GetItemsCount() - 1 : *m_position;
		m_image = m_document.GetItem(position).GetImage();
		m_document.DeleteItem(position);
	}

private:
	IDocument& m_document;
	Path m_path;
	int m_width;
	int m_height;
	std::shared_ptr<IImage> m_image;
	std::optional<size_t> m_position;
};
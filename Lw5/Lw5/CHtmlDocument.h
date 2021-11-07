#pragma once

#include "IDocument.h"
#include "CParagraph.h"
#include "CHistory.h"
#include "CImage.h"
#include "CHtmlEncoder.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

const Path IMAGE_FOLDER = "image";

class CHtmlDocument : public IDocument
{
public:
	// ��������� �������� ������ � ��������� ������� (������� ����������� ��������)
	// ���� �������� position �� ������, ������� ���������� � ����� ���������
	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		std::optional<size_t> position = std::nullopt) override
	{
		std::shared_ptr<IParagraph> paragraph = std::make_shared<CParagraph>(text);
		if (position == std::nullopt)
			m_items.push_back(CDocumentItem(paragraph));
		else
		{
			auto it = m_items.begin() + *position;
			m_items.insert(it, CDocumentItem(paragraph));
		}
		return paragraph;
	}

	// ��������� ����������� � ��������� ������� (������� ����������� ��������)
	// �������� path ������ ���� � ������������ �����������
	// ��� ������� ����������� ������ ������������ � ���������� images
	// ��� ������������� ��������������� ������
	std::shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		std::optional<size_t> position = std::nullopt) override
	{
		Path imageName(std::to_string(m_imageCounter++));
		Path newImagePath = IMAGE_FOLDER / imageName;
		newImagePath.replace_extension(path.extension());
		std::filesystem::create_directory(IMAGE_FOLDER);
		std::filesystem::copy(path, newImagePath);
		std::shared_ptr<IImage> image = std::make_shared<CImage>();
		CDocumentItem item(image);
		if (position == std::nullopt)
			m_items.push_back(item);
		else
		{
			auto it = m_items.begin() + *position;
			m_items.insert(it, item);
		}
	

		return image;
	}

	// ���������� ���������� ��������� � ���������
	size_t GetItemsCount() const override
	{
		return m_items.size();
	}

	// ������ � ��������� �����������
	CConstDocumentItem GetItem(size_t index) const override
	{
		return m_items[index];
	}

	CDocumentItem GetItem(size_t index) override
	{
		return m_items[index];
	}

	//������� ������� �� ���������
	void DeleteItem(size_t index) override
	{
		m_items.erase(m_items.begin() + index);
	}

	//���������� ��������� ���������
	std::string GetTitle() const override
	{
		return m_title;
	}

	//�������� ��������� ���������
	void SetTitle(const std::string& title) override
	{
		m_title = title;
	}

	//�������� � ����������� �������� Undo
	bool CanUndo() const override
	{
		return m_history.CanUndo();
	}

	//�������� � ����������� �������� Redo
	bool CanRedo() const override
	{
		return m_history.CanRedo();
	}

	//��������� ���������� ������� ��������������
	void Redo() override
	{
		m_history.Redo();
	}
	//�������� ������� ��������������
	void Undo() override
	{
		m_history.Undo();
	}

	void ShowItems() override
	{
		std::cout << "Title: " << m_title << std::endl;
		for (size_t i = 0; i < GetItemsCount(); ++i)
		{
			auto image = GetItem(i).GetImage();
			auto paragraph = GetItem(i).GetParagraph();
			if (image != nullptr)
				std::cout << i << ". Image: "
						  << image->GetWidth() << " "
						  << image->GetHeight() << " "
						  << image->GetPath()
						  << std::endl;
						
			if (paragraph != nullptr)
				std::cout << i << ". Paragraph: "
						  << paragraph->GetText()
						  << std::endl;
		}
	}

	// ��������� �������� � ������� html. ����������� ����������� � ���������� images.
	// ���� � ������������ ����������� ������������ ���� � ������������ HTML �����
	void Save(const Path& path) const override
	{
		std::ofstream output(path);
		output << "<html>" << std::endl;
		output << "<h1>" <<CHtmlEncoder::Encode(GetTitle()) << "</h1>" << std::endl;
		for (size_t i = 0; i < GetItemsCount(); i++)
		{
			auto item = GetItem(i);
			auto paragraph = item.GetParagraph();
			auto image = item.GetImage();
			if (paragraph != nullptr)
				output << "<p>" << CHtmlEncoder::Encode(paragraph->GetText()) << "</p>" << std::endl;
			if (image != nullptr)
				output << "<img src=\"" << CHtmlEncoder::Encode(image->GetPath().string()) << "\" width=" << image->GetWidth()
					   << "\" height=\"" << image->GetHeight() << "\" src=\"img\"/>" << std::endl;
		}
		output << "</html>";
		output.close();
		auto resultPath = path.parent_path() / IMAGE_FOLDER;
		std::filesystem::copy(
			IMAGE_FOLDER.u8string(), 
			resultPath.u8string(), 
			std::filesystem::copy_options::recursive | std::filesystem::copy_options::overwrite_existing);
	}

private:
	CHistory m_history;
	std::vector<CDocumentItem> m_items;
	std::string m_title;
	Path m_path;
	int m_imageCounter = 0;
};
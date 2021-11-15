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

	CHtmlDocument()
	{
		if (std::filesystem::exists(IMAGE_FOLDER))
			std::filesystem::remove_all(IMAGE_FOLDER);
	}

	// Вставляет параграф текста в указанную позицию (сдвигая последующие элементы)
	// Если параметр position не указан, вставка происходит в конец документа
	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		std::optional<size_t> position = std::nullopt) override
	{
		std::shared_ptr<IParagraph> paragraph = std::make_shared<CParagraph>(text);
		if (position == std::nullopt)
			m_items.push_back(CDocumentItem(paragraph));
		else
		{
			if (*position < 0 || *position >= GetItemsCount())
				throw std::invalid_argument("Invalid position argument");

			auto it = m_items.begin() + *position;
			m_items.insert(it, CDocumentItem(paragraph));
		}
		return paragraph;
	}

	// Вставляет изображение в указанную позицию (сдвигая последующие элементы)
	// Параметр path задает путь к вставляемому изображению
	// При вставке изображение должно копироваться в подкаталог images
	// под автоматически сгенерированным именем
	std::shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		std::optional<size_t> position = std::nullopt) override
	{
		Path imageName(std::to_string(m_imageCounter++));
		Path newImagePath = IMAGE_FOLDER / imageName;
		newImagePath.replace_extension(path.extension());
		std::filesystem::create_directory(IMAGE_FOLDER);

		if (std::filesystem::exists(newImagePath))
			std::filesystem::copy(path, newImagePath);

		std::shared_ptr<IImage> image = std::make_shared<CImage>(width, height, newImagePath);
		CDocumentItem item(image);
		if (position == std::nullopt)
			m_items.push_back(item);
		else
		{
			if (*position < 0 || *position >= GetItemsCount())
				throw std::invalid_argument("Invalid position argument");

			auto it = m_items.begin() + *position;
			m_items.insert(it, item);
		}
	
		return image;
	}

	// Возвращает количество элементов в документе
	size_t GetItemsCount() const override
	{
		return m_items.size();
	}

	// Доступ к элементам изображения
	CConstDocumentItem GetItem(size_t index) const override
	{
		return m_items[index];
	}

	CDocumentItem GetItem(size_t index) override
	{
		if (GetItemsCount() == 0 || index > GetItemsCount() - 1)
			throw std::out_of_range("Out of range");

		return m_items[index];
	}

	//Удаляет элемент из документа
	void DeleteItem(size_t index) override
	{
		if (GetItemsCount() == 0 || index > GetItemsCount() - 1)
			throw std::out_of_range("Out of range");

		if (GetItem(index).GetImage() != nullptr)
			--m_imageCounter;

		m_items.erase(m_items.begin() + index);
	}

	//Возвращает заголовок документа
	std::string GetTitle() const override
	{
		return m_title;
	}

	//Изменяет заголовок документа
	void SetTitle(const std::string& title) override
	{
		m_title = title;
	}

	//Сообщает о доступности операции Undo
	bool CanUndo() const override
	{
		return m_history.CanUndo();
	}

	//Сообщает о доступности операции Redo
	bool CanRedo() const override
	{
		return m_history.CanRedo();
	}

	//Выполняет отмененную команду редактирования
	void Redo() override
	{
		m_history.Redo();
	}
	//Отменяет команду редактирования
	void Undo() override
	{
		m_history.Undo();
	}

	void ShowItems(std::ostream& os) override
	{
		os << "Title: " << m_title << std::endl;
		for (size_t i = 0; i < GetItemsCount(); ++i)
		{
			auto image = GetItem(i).GetImage();
			auto paragraph = GetItem(i).GetParagraph();
			if (image != nullptr)
				os << i << ". Image: "
						  << image->GetWidth() << " "
						  << image->GetHeight() << " "
						  << image->GetPath()
						  << std::endl;
						
			if (paragraph != nullptr)
				os << i << ". Paragraph: "
						  << paragraph->GetText()
						  << std::endl;
		}
	}

	void HandleCommand(std::unique_ptr<ICommand>&& command) override
	{
		m_history.AddAndExecuteCommand(std::move(command));
	}

	// Сохраняет документ в формате html. Изображения сохраняются в подкаталог images.
	// Пути к изображениям указываются относительно пути к сохраняемому HTML файлу
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
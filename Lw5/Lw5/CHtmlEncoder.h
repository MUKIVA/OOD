#pragma once
#include <map>
#include <string>
#include <regex>

static class CHtmlEncoder
{
public:

	static std::string GetHtmlCodeByChar(const std::string& ch)
	{
		if (CharToHtmlCode.find(ch) != CharToHtmlCode.end())
			return ch;
		else
			return CharToHtmlCode.at(ch);
	}

	static std::string Encode(std::string html)
	{
		std::string result;
		std::regex reg("<|>|\"|'|&"); 
		auto matchIterator = std::sregex_iterator(html.begin(), html.end(), reg);

		if (matchIterator == std::sregex_iterator())
			return html;

		std::smatch lastMatch;
		for (auto it = matchIterator; it != std::sregex_iterator(); ++it)
		{
			std::smatch match = *it;
			result.append(match.prefix().str()).append(GetHtmlCodeByChar(match[0]));
			lastMatch = match;
		}
		result += lastMatch.suffix().str();

		return result;
	}

private:
	typedef std::map<std::string, std::string> HtmlMap;
	static HtmlMap CharToHtmlCode;
};

CHtmlEncoder::HtmlMap CHtmlEncoder::CharToHtmlCode = {
	{ "<", "&lt;" },
	{ ">", "&gt;" },
	{ "\"", "&quot;" },
	{ "'", "&apos;" },
	{ "&", "&amp;" }
};
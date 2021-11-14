#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"

#include "../Lw6Color/CRendererAdapter.h"
#include "../Lw6Color/ModernGraphicsLib.h"
#include <sstream>
#include <string>

SCENARIO("Object adapter tests")
{
	std::ostringstream oss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(oss);

	GIVEN("Standart color")
	{
		WHEN("start point is not specified")
		{
			std::string requireStr;
			CRendererAdapter(renderer).LineTo(10, 10);
			requireStr.append("<line fromX=\"0\" fromY=\"0\" toX=\"10\" toY=\"10\">\n");
			requireStr.append("\t<color r=\"0\" g=\"0\" b=\"0\" a=\"0\">\n");
			requireStr.append("</line>\n");
			REQUIRE(oss.str() == requireStr);
		}

		WHEN("start point is specified")
		{
			std::string requireStr;
			auto adapter = CRendererAdapter(renderer);
			adapter.MoveTo(100, 100);
			adapter.LineTo(10, 10);
			requireStr.append("<line fromX=\"100\" fromY=\"100\" toX=\"10\" toY=\"10\">\n");
			requireStr.append("\t<color r=\"0\" g=\"0\" b=\"0\" a=\"0\">\n");
			requireStr.append("</line>\n");
			REQUIRE(oss.str() == requireStr);
		}
	}

	GIVEN("Another color")
	{
		std::uint32_t color = 0xFF00FF;

		WHEN("start point is not specified")
		{
			std::string requireStr;
			auto adapter = CRendererAdapter(renderer);
			adapter.SetColor(color);
			adapter.LineTo(10, 10);
			requireStr.append("<line fromX=\"0\" fromY=\"0\" toX=\"10\" toY=\"10\">\n");
			requireStr.append("\t<color r=\"1\" g=\"0\" b=\"1\" a=\"0\">\n");
			requireStr.append("</line>\n");
			REQUIRE(oss.str() == requireStr);
		}

		WHEN("start point is specified")
		{
			std::string requireStr;
			auto adapter = CRendererAdapter(renderer);
			adapter.SetColor(color);
			adapter.MoveTo(100, 100);
			adapter.LineTo(10, 10);
			requireStr.append("<line fromX=\"100\" fromY=\"100\" toX=\"10\" toY=\"10\">\n");
			requireStr.append("\t<color r=\"1\" g=\"0\" b=\"1\" a=\"0\">\n");
			requireStr.append("</line>\n");
			REQUIRE(oss.str() == requireStr);
		}
	}
}

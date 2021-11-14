#define CATCH_CONFIG_MAIN

#include "../../catch2/catch.hpp"

#include "../Lw6/CRendererAdapter.h"
#include "../Lw6/ModernGraphicsLib.h"
#include <sstream>

SCENARIO("Object adapter tests")
{
	std::ostringstream oss;
	modern_graphics_lib::CModernGraphicsRenderer renderer(oss);
	
	WHEN("start point is not specified")
	{
		CRendererAdapter(renderer).LineTo(10, 10);
		REQUIRE(oss.str() == "(<line fromX=\"0\" fromY=\"0\" toX=\"10\" toY=\"10\" />)\n");
	}

	WHEN("start point is specified")
	{
		auto adapter = CRendererAdapter(renderer);
		adapter.MoveTo(100, 100);
		adapter.LineTo(10, 10);
		REQUIRE(oss.str() == "(<line fromX=\"100\" fromY=\"100\" toX=\"10\" toY=\"10\" />)\n");
	}
}
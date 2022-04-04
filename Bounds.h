#pragma once
#include <map>
#include <string>

namespace Snowy
{
	class Bounds
	{
	public:
		explicit Bounds(int b_top, int b_left, int b_right, int b_bottom);

		std::map<std::string, int> GetBounds();
	private:
		std::map<std::string, int> boundsCoordinates;
	};
}



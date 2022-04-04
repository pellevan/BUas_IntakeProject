#include "Bounds.h"

namespace Snowy
{
	Bounds::Bounds(int b_top, int b_left, int b_right, int b_bottom)
	{
		boundsCoordinates =
		{
			{"top", b_top},
			{"left", b_left},
			{"right", b_right},
			{"bottom", b_bottom}
		};
	};

	std::map<std::string, int> Bounds::GetBounds()
	{
		return boundsCoordinates;
	}

}




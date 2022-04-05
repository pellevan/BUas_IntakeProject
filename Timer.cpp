#include "Timer.h"
#include <chrono>

namespace Snowy
{
	void Timer::reset()
	{
		startTime = clock::now();
	}

	double Timer::elapsed_ms() const
	{
		return std::chrono::duration_cast<timevalue_ms>(clock::now() - startTime).count();
	}

	double Timer::elapsed_sec() const
	{
		auto elapsed_ms = std::chrono::duration_cast<timevalue_ms>(clock::now() - startTime).count();
		return elapsed_ms / 1000.0;
	}

	bool Timer::get_state() const
	{
		auto elapsed_sec = (std::chrono::duration_cast<timevalue_ms>(clock::now() - startTime).count())/1000.0;
		if (elapsed_sec > wait_time_sec) return true;

		return false;
	}
}
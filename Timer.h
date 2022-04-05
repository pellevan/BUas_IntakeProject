#pragma once
#include <chrono>


namespace Snowy
{
	class Timer
	{
	public:
		Timer(double wait_time_sec) : startTime(std::chrono::high_resolution_clock::now()), wait_time_sec(wait_time_sec) {}

		void reset(); 

		double elapsed_ms() const;
		double elapsed_sec() const;
		bool get_state() const;
	private:
		typedef std::chrono::high_resolution_clock clock;
		typedef std::chrono::seconds timevalue_sec;
		typedef std::chrono::milliseconds timevalue_ms;

		double wait_time_sec;
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	};
}

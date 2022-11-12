#include <std_include.hpp>

extern "C"
{
	int s_read_arc4random(void*, std::size_t)
	{
		return -1;
	}

#if !defined(__linux__)
	int s_read_getrandom(void*, std::size_t)
	{
		return -1;
	}
#endif

#ifdef _WIN32
	int s_read_urandom(void*, std::size_t)
	{
		return -1;
	}

	int s_read_ltm_rng(void*, std::size_t)
	{
		return -1;
	}
#else
	int s_read_wincsp(void*, std::size_t)
	{
		return -1;
	}
#endif
}

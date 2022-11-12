#ifdef _WIN32
#pragma once

#pragma warning(push)
#pragma warning(disable: 4018)
#pragma warning(disable: 4100)
#pragma warning(disable: 4127)
#pragma warning(disable: 4244)
#pragma warning(disable: 4297)
#pragma warning(disable: 4458)
#pragma warning(disable: 4702)
#pragma warning(disable: 4804)
#pragma warning(disable: 4806)
#pragma warning(disable: 4996)
#pragma warning(disable: 5054)
#pragma warning(disable: 6011)
#pragma warning(disable: 6297)
#pragma warning(disable: 6385)
#pragma warning(disable: 6386)
#pragma warning(disable: 6387)
#pragma warning(disable: 26110)
#pragma warning(disable: 26451)
#pragma warning(disable: 26444)
#pragma warning(disable: 26451)
#pragma warning(disable: 26489)
#pragma warning(disable: 26495)
#pragma warning(disable: 26498)
#pragma warning(disable: 26812)
#pragma warning(disable: 28020)

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

#endif

// min and max is required by gdi, therefore NOMINMAX won't work
#ifdef max
	#undef max
#endif

#ifdef min
	#undef min
#endif

#include <cstdio>
#include <cstdint>
#include <csignal>
#include <cstdarg>
#include <cassert>

#include <mutex>
#include <atomic>
#include <chrono>
#include <vector>
#include <thread>
#include <fstream>
#include <iostream>
#include <utility>
#include <filesystem>
#include <functional>
#include <sstream>
#include <optional>

#include <gsl/gsl>

#ifdef _WIN32
#pragma warning(pop)
#pragma warning(disable: 4100)

#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "urlmon.lib" )
#pragma comment(lib, "iphlpapi.lib")

#endif

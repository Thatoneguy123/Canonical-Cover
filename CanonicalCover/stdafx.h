#ifdef __linux__
	#define CLEARSCREEN clear()
#endif

#ifdef _WIN32
	#define CLEARSCREEN system("cls")
#endif

// Std Lib
#include <iostream>
#include <string>
#include <list>
#include <set>
#include <map>
#include <cctype>
#include <exception>
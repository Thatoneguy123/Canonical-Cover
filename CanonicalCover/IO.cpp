#include "IO.hpp"

namespace canonical {

IO::IO()
{
	// bad
#ifdef _WIN32
	system("Color 1A"); // Set console color
#endif
}

void IO::clear()
{
	CLEARSCREEN;
}

void IO::pause()
{
	cout << "Press any key to continue...";
	//cin.ignore();
	cin.get();
}

}
#ifndef IO_HPP
#define IO_HPP

#include "stdafx.h"

using namespace std;

namespace canonical{

class IO
{
private:
public:
	IO();
	void pause();
	void clear();
	void skipLine();
	int readInt();
	bool eof();
	char* readString();
	//char* readLine();
};

}

#endif
#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include "stdafx.h"

namespace canonical{

class Instance
{
private:
	char* m_name;
	char* m_value;
public:
	Instance(char* name, char*value);
	~Instance();
	char* get_name();
	char* get_value();

	bool operator==(const Instance& other);
};

}

#endif
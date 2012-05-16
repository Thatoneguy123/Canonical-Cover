#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include "stdafx.h"
#include "Instance.hpp"

namespace canonical{

class Attribute
{
private:
	std::set<char*>* m_values;
	char* m_name;
public:
	Attribute(char* name, std::set<char*>* values);
	~Attribute();
	bool isValid(Instance* instance);
	char* get_name();
	std::set<char*>* get_values();
};

}

#endif
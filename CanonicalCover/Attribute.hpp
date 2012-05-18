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

	bool operator< (Attribute& other);
};

}

// less function for ordering in set
namespace std{
	template<>
	struct less<canonical::Attribute*>
	{
		bool operator()(canonical::Attribute* a1,canonical::Attribute* a2)
		{
			return (*a1) < (*a2);
		}
	};

	// Function for sorting c strings in a set
	template <>
	struct less<char*>
	{
		bool operator()(char* c1,char* c2)
		{
			if(strcmp(c1,c2) < 0)
				return true;
			else
				return false;
		}
	};
}

#endif
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
	bool operator< (Instance& other);
};

}

namespace std{
	template<>
	struct less<canonical::Instance*>
	{
		bool operator()(canonical::Instance* i1,canonical::Instance* i2)
		{
			return (*i1) < (*i2);
		}
	};
}
#endif
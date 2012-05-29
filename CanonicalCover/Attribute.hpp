/**
 * Class implements a single attribute within a data set.
 * An attribute has a single name but mutliple unique values.
 * 
 * All values and the name are deleted upon destruction of the attribute
 */
#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include "stdafx.h"
#include "Instance.hpp"

namespace canonical{

class Attribute
{
private:
	// Set of unique values that this attribute can have
	std::set<char*>* m_values;
	// The name which identifies this attribute
	char* m_name;
public:
	// Constructor for attribute. Takes a c string name and a pointer
	// to a set of c string values. Attribute uses values that are passed in
	// and will therefore invalidate any values passed in
	Attribute(char* name, std::set<char*>* values);
	// Deleted memort allocated for name and values for this attribute
	~Attribute();
	// Checks if an instances value and name are valid according to this
	// particular object. If the instance is invalid the instance is simply
	// returned. If the instance is valid, the instances name and value
	// is deleted and replaced with the corresponding pointers from 'this'
	bool isValid(Instance* instance);
	// Returns a pointer to the name of this attribute
	char* get_name();
	// Returns a pointer to a set of c strings that are values
	// for this attribute
	std::set<char*>* get_values();

	bool operator< (Attribute& other);
};

}

// less function for ordering in set
// Attribute will be ordered in alphabetical order by name and then values
namespace std{
	template<>
	struct less<canonical::Attribute*>
	{
		bool operator()(canonical::Attribute* a1,canonical::Attribute* a2)
		{
			return (*a1) < (*a2);
		}
	};

	// Function for sorting c strings in a set. Alphabetical order
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
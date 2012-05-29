/**
 * Implements a single particular instance in a set
 * of rules.
 */
#ifndef INSTANCE_HPP
#define INSTANCE_HPP

#include "stdafx.h"

namespace canonical{

class Instance
{
private:
	// The attribute name for this instance
	char* m_name;
	// The attribute value for this instance
	char* m_value;

public:
	// Creates an instance. Assigns the points
	// as m_name and m_value. Only valid as long
	// as attribute this instance was based off
	// has not been destroyed
	Instance(char* name, char*value);
	// Destructor does nothing. Attribute definition
	// is responsible for deleting m_name and m_value
	~Instance();
	// returns actual c string m_name
	char* get_name();
	// return actual c string m_value
	char* get_value();
	// calls delete on m_name and replaces it with name
	// typically used when validating with attribute
	void set_name(char* name);
	// calls delete on m_value and replaces it with value
	// typicall used when validating with attribute
	void set_value(char* value);

	// Checks if two instances are equal. Equal when 
	// m_name and m_value are both equal
	bool operator==(const Instance& other);
	// Check if value is less than other instance.
	// less than if checks m_name first based on alphabetical order.
	// if equal then runs same comparison on m_value
	bool operator< (Instance& other);
};

}

// Used for sorting the instance in a set
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
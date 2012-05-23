#include "Instance.hpp"

namespace canonical{

Instance::Instance(char* name, char* value)
{
	m_name = name;
	m_value = value;
}

// The memory used by m_name and m_value
// is a pointer to the values in an attribute object
// it is not the Instances responsibility to free
Instance::~Instance()
{

}

char* Instance::get_name()
{
	return m_name;
}

char* Instance::get_value()
{
	return m_value;
}

bool Instance::operator<(Instance& other)
{
	// Check names first
	int result = strcmp(get_name(),other.get_name() );
	
	// This comes before other in alphabet
	if( result < 0 )
		return true;
	else
		if( result == 0) // Equal so check values
		{
			result = strcmp(get_value(),other.get_value());
			// This value comes before other
			if( result < 0)
				return true;
		}

	// this comes After other so its greater than
	return false;
}

bool Instance::operator==(const Instance& other)
{
	return ( !strcmp(m_name,other.m_name) && !strcmp(m_value,other.m_value) );
}

void Instance::set_name(char* name)
{
	delete m_name;
	m_name = name;
}

void Instance::set_value(char* value)
{
	delete m_value;
	m_value = value;
}

}
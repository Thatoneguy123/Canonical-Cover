#include "Instance.hpp"

namespace canonical{

Instance::Instance(char* name, char* value)
{
	m_name = name;
	m_value = value;
}

Instance::~Instance()
{
	delete m_name;
	delete m_value;
}

char* Instance::get_name()
{
	return m_name;
}

char* Instance::get_value()
{
	return m_value;
}

bool Instance::operator==(const Instance& other)
{
	return ( !strcmp(m_name,other.m_name) && !strcmp(m_value,other.m_value) );
}

}
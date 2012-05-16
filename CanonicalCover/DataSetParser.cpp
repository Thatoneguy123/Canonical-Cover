#include "DataSetParser.hpp"

using namespace std;
namespace canonical {

DataSetParser::DataSetParser(IO* io)
{
	m_dataSet = new DataSet();
	m_io = io;
}

DataSet* DataSetParser::parseFromInput()
{
	parseAttributes();

	return m_dataSet;
}

void DataSetParser::parseAttributes()
{
	// Get the number of attributes
	int number = m_io->readInt();
	m_io->skipLine();

	// Create the attributes
	for(int i = 0; i < number; i++)
	{
		// Get attribute name
		char* name = m_io->readString();

		// Get values for the attribute
		set<char*>* values = new set<char*>();

		// Read first attribute
		char* value = m_io->readString();
		// Read until null is returned for end of line
		while( value != NULL )
		{
			values->insert(value);
			value = m_io->readString();
		}
		if( values->count() < 1)
			throw runtime_error("Error Parsing Attributes. No values specified.");
		// Create the attribute
		Attribute* attribute = new Attribute(name,values);
		// Add attribute to the data set
		m_dataSet->addAttributeDefinition(attribute);
	}

	int i;
	cin >> i;
}

}
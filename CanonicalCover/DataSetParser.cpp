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
	parseRules();

	return m_dataSet;
}

// Takes a string of format <str1>=<str2> and creates an
// instance from it
Instance* DataSetParser::parseInstance(char* input)
{
	size_t szStr1 = 0;
	size_t szStr2 = 0;
	size_t index = 0;
	
	// Dangerous no check to ensure its in bounds!
	// Get size of name
	while( input[index] != '=')
	{
		szStr1++;
		index++;
	}

	// Get past the = sign
	index++;
	// Get size of value
	while(input[index] != '\0')
	{
		szStr2++;
		index++;
	}
	// Create buffer for name
	char* name = (char*)malloc(sizeof(char) * (szStr1+1));
	// Create buffer for value
	char* value = (char*)malloc(sizeof(char) * (szStr2+1));

	//populate name
	for(size_t i = 0; i < szStr1; i++)
		name[i] = input[i];
	name[szStr1] = '\0';

	//populate value
	for(size_t i = 0; i < szStr2; i++)
		value[i] = input[i+szStr1+1];
	value[szStr2] = '\0';

	// Create the instance
	Instance *instance = new Instance(name,value);

	// Verify this instance can exist within the attribute definitions
	if( m_dataSet->isValid(instance) )
		return(instance);
	else
	{
		// delete the invalid name and value
		delete name;
		delete value;
		// delete the instance
		delete instance;
		throw runtime_error("Error parsing rule. No attribute defintion "
			"exists for instance.");
	}
}

void DataSetParser::parseRules()
{
	// Get the number of rules
	int number = m_io->readInt();
	m_io->skipLine();
	
	// Create the rules
	for(int i = 0; i < number; i++)
	{
		// Parse antecedents first
		bool antecedent = true;

		Rule* rule = new Rule();
		// Read the first instance of the rule
		char* input = m_io->readString();

		while(input != NULL)
		{
			// Check if switching to consequents
			if( !strcmp(input,"==") )
			{
				antecedent = false;
				delete input;
			}
			else // Parsing an instance
			{
				Instance* instance = parseInstance(input);
				// Free the input
				delete input;
				
				// Add the instance to the correct list
				if(antecedent)
					rule->add_antecedent(instance);
				else
					rule->add_consequent(instance);
			}

			//Read next input
			input = m_io->readString();
		}

		// Check if no instances were added to rule
		if(rule->get_antecedents()->size() == 0 ||
			rule->get_consequents()->size() == 0)
		{
			delete rule;
			throw runtime_error("Error parsing rule. No instances defined.");
		}

		// Add the rule to the dataset
		m_dataSet->addRuleDefinition(rule);
	}
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
		if( values->size() < 1)
			throw runtime_error("Error Parsing Attributes. No values specified.");
		// Create the attribute
		Attribute* attribute = new Attribute(name,values);
		// Add attribute to the data set
		m_dataSet->addAttributeDefinition(attribute);
	}
}

}
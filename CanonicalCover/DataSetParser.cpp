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

	char* input = m_io->readString();
	cout << input << endl;
	m_io->readString();
	input = m_io->readString();
	cout << input << endl;

	if(input == NULL)
		cout << "END OF LINE" << endl;

	cin >> number;
}

}
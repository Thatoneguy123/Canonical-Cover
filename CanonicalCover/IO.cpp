#include "IO.hpp"

namespace canonical {

IO::IO()
{
	// bad
#ifdef _WIN32
	system("Color 1A"); // Set console color
#endif
}

void IO::clear()
{
	CLEARSCREEN;
}

void IO::pause()
{
	cout << "Press any key to continue...";
	cin.get();
}

void IO::skipLine()
{
	char buf;
	cin.get(buf);

	while( buf != '\n' && !eof())
			cin.get(buf);
}

int IO::readInt()
{
	if( eof() )
		throw runtime_error("Error parsing. Expecting INT but found EOF");
	char buf;
	cin.get(buf);

	if( isdigit(buf) )
		return atoi(&buf);
	else
		throw runtime_error("Error parsing. Expecting INT but found non INT value");
}
// Reads the next string delimited by whitespace.
// stops BEFORE \n leaving it in buffer.
char* IO::readString()
{
	if( eof() )
		throw runtime_error("Error parsing. Expecting STRING but found EOF");
	
	int sz = 1;
	int written = 0;
	char* temp = (char*)malloc(sizeof(char) * (sz+1));
	char* buffer;
	char in;
	in = cin.peek();
	
	// Read first char
	cin.get(in);

	if(in == '\n')
	{
		delete temp;
		return NULL;
	}

	// Loop while alphanumeric or puncuation and not end of file
	while( (ispunct(in) || isalnum(in)) && !eof() )
	{
		// Make new buffer if no space is left
		if(written == sz)
		{
			buffer = temp;
			// Double the size
			sz = (sz+sz);
			// Make temp twice the size + 1 for null terminator
			temp = (char*)malloc(sizeof(char)*(sz+1));
			// Copy values into new resized array
			for(int i = 0; i < written; i++)
				temp[i] = buffer[i];
			// Delete the old array
			delete buffer;
		}
		// Assign input to the array
		temp[written] = in;
		written++;

		// Quit if new line appears
		if(cin.peek() == '\n')
			break;

		cin.get(in);
	}

	// Insert null terminator
	temp[written] = '\0';
	return temp;
}

bool IO::eof()
{
	return cin.eofbit == cin.peek();
}

}
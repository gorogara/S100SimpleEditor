#include "stdafx.h"
#include "WStringToken.h"

using namespace std;
GMLStringTokenizer::GMLStringTokenizer(const string& inputstring, const string& seperator)
	: _input(inputstring), _delimiter(seperator)
{
	split();
}

GMLStringTokenizer::~GMLStringTokenizer()
{

}

size_t GMLStringTokenizer::countTokens()
{
	return token.size();
}

bool GMLStringTokenizer::hasMoreTokens()
{
	return index != token.end();
}

string GMLStringTokenizer::nextToken()
{
	if (index != token.end()) return *(index++);
	else return "";
}

void GMLStringTokenizer::split()
{
	string::size_type lastPos = _input.find_first_not_of(_delimiter, 0); 
	string::size_type Pos = _input.find_first_of(_delimiter, lastPos); 

	while (string::npos != Pos || string::npos != lastPos)
	{
		token.push_back(_input.substr(lastPos, Pos - lastPos));
		lastPos = _input.find_first_not_of(_delimiter, Pos); 
		Pos = _input.find_first_of(_delimiter, lastPos); 
	}

	index = token.begin();
}

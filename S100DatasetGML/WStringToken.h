#pragma once

#include <vector>
#include <string>

class GMLStringTokenizer
{
public:
	GMLStringTokenizer(const std::string& inputstring, const std::string& seperator);
	virtual ~GMLStringTokenizer();

private:
	std::string _input;
	std::string _delimiter;
	std::vector<std::string> token;
	std::vector<std::string>::iterator index;

public:
	size_t countTokens(); 
	bool hasMoreTokens(); 
	std::string nextToken(); 
	void split(); 
};
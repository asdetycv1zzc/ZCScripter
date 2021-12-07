#include<iostream>
#include<string>
#include"Converter.h"
using namespace std;

StringStruct UCS_2_TO_UTF_8(StringStruct UCS_2)
{
	string _source(UCS_2.Content);
	string _dest;

	long long i = 0;
	while (i < UCS_2.CharacterAmount)
	{
		_dest.push_back(UCS_2.Content[i]);
		i += 2;
	}
	StringStruct _result;
	_result.Content = _dest;
	_result.CharacterAmount = _result.Content.size();
	return _result;
}
string UCS_2_TO_UTF_8(string UCS_2)
{
	string _source(UCS_2);
	string _result;

	unsigned long long i = 0;
	while (i < UCS_2.size())
	{
		_result.push_back(UCS_2[i]);
		i += 2;
	}
	return _result;
}
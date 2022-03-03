#include<iostream>
#include<string>
#include<wstring_extend.h>
using namespace std;

size_t wstrlen(const wchar_t* _a)
{
	size_t _result = 0;
	while (*(_a + _result) != L'\0') _result += 1;
	return _result;
}
bool wstrcmp(const wchar_t* _a, const wchar_t* _b)
{
	if (wstrlen(_a) != wstrlen(_b)) return false;
	auto _size = wstrlen(_a);
	for (size_t i = 0; i < _size; i++)
	{
		if (*(_a + i) != *(_b + i)) return false;
	}
	return true;
}
#pragma once
#include<iostream>
#include<string>
#include<Windows.h>
#include<tchar.h>
#include<clocale>
struct StringStruct
{
	std::string Content;
	long long CharacterAmount = -1;
};

StringStruct UCS_2_TO_UTF_8(StringStruct UCS_2);
std::string UCS_2_TO_UTF_8(std::string UCS_2);
std::string WStringToString(const std::wstring& ws);
std::wstring StringToWString(const std::string& str);
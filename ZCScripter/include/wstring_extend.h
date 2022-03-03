#pragma once
#include<iostream>
#include<string>
#include<vector>

size_t wstrlen(const wchar_t* _a);
bool wstrcmp(const wchar_t* _a, const wchar_t* _b);
std::vector<std::wstring> splitwstr(const std::wstring& _source, const std::wstring& _seperate);
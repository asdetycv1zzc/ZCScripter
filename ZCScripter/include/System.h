#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<map>

class QLIESystem
{
private:
	const std::wstring _G;
public:
	std::wstring SelfFileName;
	std::wstring RootFile;
	std::vector<std::wstring> ResultStr;
	std::vector<std::wstring> Avg_SelectCurLabel;
	std::wstring FragResult;
	std::vector<std::wstring> ParamStr;

	QLIESystem(const std::wstring& k_ScriptAddress);
	QLIESystem(const wchar_t* k_ScriptAddress);
	QLIESystem(const char* k_ScriptAddress);
	QLIESystem(const std::string& k_ScriptAddress);
	~QLIESystem();
};